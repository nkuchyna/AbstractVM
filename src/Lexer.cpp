/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 16:05:34 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/22 16:05:36 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"
#include <sys/stat.h>

Lexer::Lexer() {
	
	this->initData();
	this->_is = &std::cin;
	this->_streamType = CIN;
	this->_fileName = "none";
}

Lexer::Lexer(const std::string &fileName) {

	struct stat status;

	if (stat(fileName.c_str(), &status) == 0 && status.st_mode & S_IFDIR)
		throw Lexer::NoSuchFileException("Error! Passed parameter is a folder!");
	this->initData();
	std::ifstream  *myFile = new std::ifstream(fileName);
	this->_is = myFile;
	this->_fileName = fileName;
	_streamType = FILE;
	if (!myFile->is_open()) {
		delete this->_is;
		throw Lexer::NoSuchFileException();
	}
}

Lexer::~Lexer() {
	
	if (_streamType == FILE)
		delete this->_is;
}

Lexer::Lexer(const Lexer &obj) {
	
	*this = obj;
	return; 
}

Lexer& Lexer::operator=(Lexer const &obj) {
	
	if (&obj != this)
	{
		this->_is = new std::ifstream(obj._fileName);
		this->_streamType = obj._streamType;
		this->s_mapInstuctionType = obj.s_mapInstuctionType;
		this->s_mapOperandType = obj.s_mapOperandType;
		this->_fileName = obj._fileName;
	}
	return (*this);
}

int Lexer::getRawData(std::string *rawLine) const {

	if (!(std::getline(*this->_is, *rawLine, '\n')))
		return (0);
	return (1);
}

int Lexer::getStreamType() const {
	return(this->_streamType);
}

int	Lexer::isNumber(std::string nbrStr) {

	int		pointNbr = 0;
	size_t		i = 0;

	if ((!(std::isdigit(nbrStr[i])) && nbrStr[i] != '-')
		|| (nbrStr[0] == '0' &&  nbrStr.size() != 1 && nbrStr[1] != '.')
		|| (nbrStr[0] == '-' && nbrStr[1] == '0' &&  nbrStr.size() == 2))
	{
		throw Lexer::InvalidNumberException("Error! Invalid character at the beginning of a number.");
		return (ERROR);
	}
	while (++i < nbrStr.size())
	{
		if (!(std::isdigit(nbrStr[i])) && nbrStr[i] != '.')
		{
			throw Lexer::InvalidNumberException("Error! The number can consist of numbers and a single dot.");
			return (ERROR);
		}
		else if (nbrStr[i] == '.')
			pointNbr++;
	}
	if (!(i == nbrStr.size() && pointNbr <= 1))
	{
		throw Lexer::InvalidNumberException();
		return (ERROR);
	}
	return (1);
}

int	Lexer::isValidOperand(std::string operand, Token *obj) {

	std::map<std::string, eOperandType>::iterator it;
	std::string		operandType;

	operandType = operand.substr(0, operand.find("("));
	for (it = s_mapOperandType.begin(); it != s_mapOperandType.end(); it++)
	{
		if (operandType == it->first && operand.find(")") == operand.size() - 1)
		{
			obj->setOperandType(it->second);
			obj->setOperandValue(operand.substr(operand.find("(") + 1, operand.find(")") - operand.find("(") - 1));
			return (isNumber(obj->getOperandValue()));
		}
	}
	return (ERROR);
}

void Lexer::trimString(std::string &str) {

	std::string		spaces = " ";

	if (str.size() == 0)
		return;
	std::replace(str.begin(), str.end(), '\t', ' ');
	const unsigned long strBegin = str.find_first_not_of(spaces);
	if (strBegin == std::string::npos)
		str = "";
	const unsigned long strEnd = str.find_last_not_of(spaces);
	if (strEnd == std::string::npos)
		return;
	str = str.substr(strBegin, strEnd - strBegin + 1);
}

int	Lexer::isValidToken(std::string token, Token *obj) {

	std::map<std::string,eInstuctionType>::iterator it;
	std::string		instruction;
	std::string 	operandStr;

	obj->setOperandType(DefaultOperandType);
	obj->setOperandValue("none");
	obj->setInstructionType(DefaultInstuctionType);
	this->trimString(token);
	instruction = token.substr(0, token.find(" "));
	for (it = s_mapInstuctionType.begin(); it != s_mapInstuctionType.end(); it++)
	{
		if (instruction == it->first) {
			 obj->setInstructionType(it->second);
			 switch(s_mapInstuctionType[instruction])
			 {
			 	case Push: case Assert: case Equal:
					operandStr = token.substr(token.find(" ") + 1, token.size() - 1);
					this->trimString(operandStr);
					return (isValidOperand(operandStr, obj));
				default:
					if (it->first.compare(token.substr(token.find("\0"))) != 0)
						return(ERROR);
					return (1);
			 }
		}
	}
	return (ERROR);
}

int Lexer::buildLexema(Token *obj) {

	std::string		rawLine;
	std::string		tokenStr;
	int				ret = 0;

	if ((ret = getRawData(&rawLine)))
	{
		//this->trimString(rawLine);
		obj->incrementLineNbr();
		if (rawLine.size() == 0)
			return (EMPTY_LINE);
		tokenStr = rawLine.substr(0, rawLine.find(";"));
		if (tokenStr.size() == 0 && ((rawLine.compare(";;") != 0 && _streamType == CIN) || _streamType == FILE))
			return (COMMENT_IN_THE_STREAM);
		else if ((ret = isValidToken(tokenStr, obj)) == ERROR && rawLine.compare(";;") == 0
			&& _streamType == CIN)
			return (END_OF_THE_CIN_STREAM);
	}
	return (ret);
}

void	Lexer::initData() {

	//initialization of InstuctionType map
	this->s_mapInstuctionType["pop"] = Pop;
	this->s_mapInstuctionType["dump"] = Dump;
	this->s_mapInstuctionType["assert"] = Assert;
	this->s_mapInstuctionType["add"] = Add;
	this->s_mapInstuctionType["sub"] = Sub;
	this->s_mapInstuctionType["mul"] = Mul;
	this->s_mapInstuctionType["div"] = Div;
	this->s_mapInstuctionType["mod"] = Mod;
	this->s_mapInstuctionType["print"] = Print;
	this->s_mapInstuctionType["push"] = Push;
	this->s_mapInstuctionType["exit"] = Exit;
	this->s_mapInstuctionType["equal"] = Equal;
	this->s_mapInstuctionType["compare"] = Compare;
	this->s_mapInstuctionType["square"] = Square;
	this->s_mapInstuctionType["clear"] = Clear;
	this->s_mapInstuctionType["min"] = Min;
	this->s_mapInstuctionType["max"] = Max;

	//initialization of OperandType map
	this->s_mapOperandType["int8"] = Int8;
	this->s_mapOperandType["int16"] = Int16;
	this->s_mapOperandType["int32"] = Int32;
	this->s_mapOperandType["float"] = Float;
	this->s_mapOperandType["double"] = Double;
}

//**********EXEPTIONS*************************************************************
Lexer::NoSuchFileException::NoSuchFileException()throw() : std::exception() {
	this->_errorMessage = "Error! There is no such file!";
}

Lexer::NoSuchFileException::NoSuchFileException(const std::string errorMessage)throw() : std::exception() {
	this->_errorMessage = errorMessage;
}

Lexer::NoSuchFileException::~NoSuchFileException()throw() {}

Lexer::NoSuchFileException::NoSuchFileException(const NoSuchFileException &obj) {
	*this = obj;
	return;
}

Lexer::NoSuchFileException& Lexer::NoSuchFileException::operator=(NoSuchFileException const &obj) {
	static_cast<void>(obj);
	return (*this);
}

const char *Lexer::NoSuchFileException::what () const throw() {
	return (this->_errorMessage.c_str());
}

//***************************************************************
Lexer::InvalidNumberException::InvalidNumberException()throw() : std::exception() {
	this->_errorMessage = "Error! Invalid number!";
}
Lexer::InvalidNumberException::InvalidNumberException(std::string errorMessage)throw() : std::exception() {
	this->_errorMessage = errorMessage;
}

Lexer::InvalidNumberException::~InvalidNumberException()throw() {}

Lexer::InvalidNumberException::InvalidNumberException(const InvalidNumberException &obj) {
	*this = obj;
	return;
}

Lexer::InvalidNumberException& Lexer::InvalidNumberException::operator=(InvalidNumberException const &obj) {
	if (this != &obj)
		this->_errorMessage = obj._errorMessage;
	return (*this);
}

const char *Lexer::InvalidNumberException::what () const throw() {
	return (this->_errorMessage.c_str());
}
