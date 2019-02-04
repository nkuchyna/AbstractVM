/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 17:12:38 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/28 17:12:40 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEC_HPP
#define PARSEC_HPP
#include "Lexer.hpp"
#include "eOperand.hpp"
#include "Token.hpp"
#include "OperandFactory.hpp"
#include "Executor.hpp"
#include "AbstractVM.hpp"

class  Parser {

private:
	Lexer		*_lexer;
	Token		*_token;
	Executor	*_executor;

public:
	 Parser();
	 Parser(const std::string &file);
	 Parser(const Parser &obj);
	 Parser& operator=(const Parser &obj);
	 ~ Parser();

	 void	dataStreamProcessing();

	class NotAppropriateExitException : public std::exception {
	std::string		_errorMessage;
	public:
		NotAppropriateExitException()throw();
		NotAppropriateExitException(const std::string errorMessage)throw();
		virtual ~NotAppropriateExitException()throw();
		NotAppropriateExitException(const NotAppropriateExitException &obj);
		NotAppropriateExitException& operator=(NotAppropriateExitException const &obj);
		virtual const char *what() const throw(); 
	};

	class UnknownInstructionException : public std::exception {
	public:
		UnknownInstructionException()throw();
		virtual ~UnknownInstructionException()throw();
		UnknownInstructionException(const UnknownInstructionException &obj);
		UnknownInstructionException& operator=(UnknownInstructionException const &obj);
		virtual const char *what() const throw(); 
	};
};

#endif
