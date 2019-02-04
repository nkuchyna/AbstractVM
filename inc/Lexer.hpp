/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 16:05:20 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/22 16:05:22 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
#define LEXER_HPP
#include "AbstractVM.hpp"
#include "Token.hpp"

class Lexer {

private:
	std::istream							*_is;
	int										_streamType;
	std::string								_fileName;
	std::map<std::string, eInstuctionType>	s_mapInstuctionType;
	std::map<std::string, eOperandType>		s_mapOperandType;

public:
	Lexer();
	Lexer(const std::string &fileName);
	~Lexer();
	Lexer(const Lexer &obj);
	Lexer& operator=(Lexer const &obj);

	int 	getRawData(std::string *line) const;
	int 	getStreamType() const;
	int		isNumber(std::string nbrStr);
	int		isValidOperand(std::string operand, Token *obj);
	int		isValidToken(std::string token, Token *obj);
	int		buildLexema(Token *obj);
	void	initData();
	void	trimString(std::string &str);

	class NoSuchFileException : public std::exception {
	public:
		std::string		_errorMessage;
		NoSuchFileException()throw();
		NoSuchFileException(const std::string errorMessage)throw();
		virtual ~NoSuchFileException()throw();
		NoSuchFileException(const NoSuchFileException &obj);
		NoSuchFileException& operator=(NoSuchFileException const &obj);
		virtual const char *what() const throw(); 
	};

	class InvalidNumberException : public std::exception {
	std::string		_errorMessage;
	public:
		InvalidNumberException()throw();
		InvalidNumberException(const std::string errorMessage)throw();
		virtual ~InvalidNumberException()throw();
		InvalidNumberException(const InvalidNumberException &obj);
		InvalidNumberException& operator=(InvalidNumberException const &obj);
		virtual const char *what() const throw(); 
	};

	class InvalidOperandException : public std::exception {
	std::string		_errorMessage;
	public:
		InvalidOperandException()throw();
		virtual ~InvalidOperandException()throw();
		InvalidOperandException(const InvalidOperandException &obj);
		InvalidOperandException& operator=(InvalidOperandException const &obj);
		virtual const char *what() const throw(); 
	};
};

#endif