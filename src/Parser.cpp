/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 17:12:32 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/28 17:12:33 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "NewStack.cpp"

Parser::Parser() {

	this->_lexer = new Lexer();
	this->_token = new Token();
	this->_executor = new Executor(*this->_token);
}

Parser::Parser(const std::string &file) {

	this->_lexer = new Lexer(file);
	this->_token = new Token();
	this->_executor = new Executor(*this->_token);
}

Parser::Parser(const Parser &obj) {
	*this = obj;
	return;
}

Parser& Parser::operator=(const Parser &obj) {
	if (this != &obj)
	{
		this->_lexer = new Lexer(*obj._lexer);
		this->_token = new Token(*obj._token);
		this->_executor = new Executor(*obj._executor);
	}
	return (*this);
}

Parser::~Parser() {
	delete this->_lexer;
	delete this->_token;
}

void Parser::dataStreamProcessing() {

	int				retLexemaBuild = 0;
	static int		retTokenProcessing = 1;

	while (1)
	{
		try 
		{
			if ((retLexemaBuild = this->_lexer->buildLexema(this->_token)) == COMMENT_IN_THE_STREAM || retLexemaBuild == EMPTY_LINE)
				continue;	
			else if (retLexemaBuild == ERROR)
				throw Parser::UnknownInstructionException();
			else if ((retLexemaBuild == END_OF_THE_STREAM && retTokenProcessing != END_OF_THE_STREAM) || retLexemaBuild == END_OF_THE_CIN_STREAM)
				throw Parser::NotAppropriateExitException();
			else if (((retTokenProcessing = this->_executor->tokenProcessing()) == END_OF_THE_STREAM)
			&& _lexer->getStreamType() == CIN && this->_lexer->buildLexema(this->_token) != END_OF_THE_CIN_STREAM)
				throw Parser::NotAppropriateExitException("Error! ;; should follow the exit instruction!");
			else if (retTokenProcessing == END_OF_THE_STREAM)
				break;
		}
		catch (const std::exception &ex)
		{
			std::cout << RED_COLOR <<"Line" << this->_token->getLineNbr() << " : " <<ex.what() << END_COLOR << std::endl;
			if (dynamic_cast<const NotAppropriateExitException*>(&ex) != NULL)
				break;
		}
	}
}

//**********************
Parser::NotAppropriateExitException::NotAppropriateExitException()throw() : std::exception() {
	this->_errorMessage = "Error! There is no exit instruction!";
}

Parser::NotAppropriateExitException::NotAppropriateExitException(const std::string errorMessage)throw() : std::exception() {
	this->_errorMessage = errorMessage;
}

Parser::NotAppropriateExitException::~NotAppropriateExitException()throw() {}

Parser::NotAppropriateExitException::NotAppropriateExitException(const NotAppropriateExitException &obj) {
	*this = obj;
	return;
}

Parser::NotAppropriateExitException& Parser::NotAppropriateExitException::operator=(NotAppropriateExitException const &obj) {
	static_cast<void>(obj);
	return (*this);
}

const char *Parser::NotAppropriateExitException::what () const throw() {
	return this->_errorMessage.c_str();
}
//**********************
Parser::UnknownInstructionException::UnknownInstructionException()throw() : std::exception() {}

Parser::UnknownInstructionException::~UnknownInstructionException()throw() {}

Parser::UnknownInstructionException::UnknownInstructionException(const UnknownInstructionException &obj) {
	*this = obj;
	return;
}

Parser::UnknownInstructionException& Parser::UnknownInstructionException::operator=(UnknownInstructionException const &obj) {
	static_cast<void>(obj);
	return (*this);
}

const char *Parser::UnknownInstructionException::what () const throw() {
	return "Error! Unknown instruction!";
}
