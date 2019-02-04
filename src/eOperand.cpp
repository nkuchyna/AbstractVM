/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eOperand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:03:45 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/23 13:03:47 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eOperand.hpp"

template <typename T>
EOperand<T>::EOperand() : _type(Int16), _precision(Int16Prec), _rawValue(0) {
	this->_strValue = std::to_string(this->_rawValue);
}

template <typename T>
EOperand<T>::EOperand(eOperandType type, int precision, T rawValue): _type(type), _precision(precision), _rawValue(rawValue) {
	this->_strValue = std::to_string(this->_rawValue);
}

template <typename T>
EOperand<T>::~EOperand() {
}

template <typename T>
EOperand<T>::EOperand(const EOperand<T> &obj){
	*this = obj;
	return;
}

template <typename T>
EOperand<T>& EOperand<T>::operator=(const EOperand<T> &obj) {
	if (&obj != this)
	{
		this->_strValue = obj._strValue;
		this->_type = obj._type;
		this->_precision = obj._precision;
		this->_rawValue = obj._rawValue;
		this->_strValue = obj._strValue;
		this->_operandFactory = obj._operandFactory;
	}
	return (*this);
}

template <typename T>
int EOperand<T>::getPrecision(void) const {
	return (this->_precision);
}

template <typename T>
eOperandType EOperand<T>::getType(void) const {
	return (this->_type);
}

template <typename T>
std::string const &EOperand<T>::toString(void) const {
	return (this->_strValue);
}

template <typename T>
IOperand const * EOperand<T>::operator+(IOperand const &rhs) const {

	eOperandType	type = DefaultOperandType;
	
	if (this->getPrecision() >= rhs.getPrecision())
		type = this->getType();
	else
		type = rhs.getType();
	return(this->_operandFactory.createOperand(type, std::to_string(std::stod(this->toString()) + std::stod(rhs.toString()))));
}

template <typename T>
IOperand const * EOperand<T>::operator-(IOperand const &rhs) const {
	
	eOperandType	type = DefaultOperandType;
	
	if (this->getPrecision() >= rhs.getPrecision())
		type = this->getType();
	else
		type = rhs.getType();
	return(this->_operandFactory.createOperand(type, std::to_string(std::stod(this->toString()) - std::stod(rhs.toString()))));
}

template <typename T>
IOperand const * EOperand<T>::operator*(IOperand const &rhs) const {
	
	eOperandType	type = DefaultOperandType;
	
	if (this->getPrecision() >= rhs.getPrecision())
		type = this->getType();
	else
		type = rhs.getType();
	return(this->_operandFactory.createOperand(type, std::to_string(std::stod(this->toString()) * std::stod(rhs.toString()))));

}

template <typename T>
IOperand const * EOperand<T>::operator/(IOperand const &rhs) const {
	
	eOperandType	type = DefaultOperandType;
	
	if (this->getPrecision() >= rhs.getPrecision())
		type = this->getType();
	else
		type = rhs.getType();
	return(this->_operandFactory.createOperand(type, std::to_string(std::stod(this->toString()) / std::stod(rhs.toString()))));
}

template <typename T>
IOperand const * EOperand<T>::operator%(IOperand const &rhs) const {

	eOperandType	type = DefaultOperandType;
	
	if (this->getPrecision() >= rhs.getPrecision())
		type = this->getType();
	else
		type = rhs.getType();
	return(this->_operandFactory.createOperand(type, std::to_string(std::stoi(this->toString()) % std::stoi(rhs.toString()))));
}

template <typename T>
bool	EOperand<T>::operator!=(IOperand const &rhs) const {

	eOperandType	type = DefaultOperandType;
	
	if (this->getPrecision() >= rhs.getPrecision())
		type = this->getType();
	else
		type = rhs.getType();

	return (static_cast<T>(std::stod(this->toString())) != std::stod(rhs.toString()));
}

template <typename T>
bool	EOperand<T>::operator>(IOperand const &rhs) const {

	eOperandType	type = DefaultOperandType;
	
	if (this->getPrecision() >= rhs.getPrecision())
		type = this->getType();
	else
		type = rhs.getType();
	return (static_cast<T>(std::stod(this->toString())) > std::stod(rhs.toString()));
}
