/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 21:08:30 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/23 21:08:31 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token() : _instructionType(DefaultInstuctionType), _operandType(DefaultOperandType),
				_operandValue("none") {}

Token::~Token() {}

Token::Token(const Token &obj) {
	*this = obj;
	return;
}

Token& Token::operator=(const Token &obj) {

	if (&obj != this)
	{
		this->_lineNbr = obj._lineNbr;
		this->_instructionType = obj._instructionType;
		this->_operandType = obj._operandType;
		this->_operandValue = obj._operandValue;
	}
	return (*this);
}

eInstuctionType	Token::getInstructionType() const {
	return (this->_instructionType);
}

eOperandType	Token::getOperandType() const {
	return (this->_operandType);
}

std::string		Token::getOperandValue() const {
	return (this->_operandValue);
}

int				Token::getLineNbr() const {
	return (this->_lineNbr);
}

void			Token::setInstructionType(const int type) {
	
	if (type >= Pop && type <= DefaultInstuctionType)
		this->_instructionType = static_cast<eInstuctionType>(type);
}

void			Token::setOperandType(const int type) {
	
	if (type >= Int8 && type <= DefaultOperandType)
		this->_operandType = static_cast<eOperandType>(type);
}

void			Token::setOperandValue(const std::string operandValue) {
	this->_operandValue = operandValue;
}

void			Token::incrementLineNbr() {
	++this->_lineNbr;
}

int Token::_lineNbr = 0;
