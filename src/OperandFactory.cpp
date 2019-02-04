/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:24:57 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/22 15:24:58 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.hpp"
#include "eOperand.cpp"

OperandFactory::OperandFactory() {
	actions[0] = &OperandFactory::createInt8;
	actions[1] = &OperandFactory::createInt16;
	actions[2] = &OperandFactory::createInt32;
	actions[3] = &OperandFactory::createFloat;
	actions[4] = &OperandFactory::createDouble;
}

OperandFactory::~OperandFactory() {}

OperandFactory::OperandFactory(const OperandFactory &obj) {
	
	*this = obj;
	return;
}

OperandFactory& OperandFactory::operator=(const OperandFactory &obj) {

	static_cast<void>(obj);
	return(*this);
}

IOperand const * OperandFactory::createOperand(eOperandType type, std::string const & value) const{
	return((this->*actions[type])(value));
}

template <typename T>
bool	OperandFactory::checkValue(const std::string value) const {

	T		type;
	return((std::istringstream(value) >> type >> std::ws).eof());
}

void	OperandFactory::checkIntValue(double value, eOperandType type) const {

	if (type >= Float)
		throw OperandFactory::ValueException();
	if (value > valueRanges[type][1])
		throw OperandFactory::ValueException("Error! Overflow on a value!");
	else if (value < valueRanges[type][0])
		throw OperandFactory::ValueException("Error! Underflow on a value!");
}

IOperand const * OperandFactory::createInt8(std::string const & value) const{

	double		tokenValue = std::stod(value);

	this->checkIntValue(tokenValue, Int8);
	return(new EOperand<int8_t>(Int8, Int8Prec, static_cast<int8_t>(tokenValue)));
}

IOperand const * OperandFactory::createInt16(std::string const & value) const{

	double		tokenValue = std::stod(value);

	this->checkIntValue(tokenValue, Int16);
	return(new EOperand<int16_t>(Int16, Int16Prec, static_cast<int16_t>(tokenValue)));
}

IOperand const * OperandFactory::createInt32(std::string const & value) const{

	double		tokenValue = std::stod(value);

	this->checkIntValue(tokenValue, Int32);
	return(new EOperand<int32_t>(Int32, Int32Prec, static_cast<int32_t>(tokenValue)));
}

IOperand const * OperandFactory::createFloat(std::string const & value) const{

	if (!(this->checkValue<float>(value)))
		throw OperandFactory::ValueException();
	try
	{
		std::stof(value);
	}
	catch (...)
	{
		throw OperandFactory::ValueException(); 
	}
	return(new EOperand<float>(Float, FloatPrec, std::stof(value)));
}

IOperand const * OperandFactory::createDouble(std::string const & value) const{
	
	if (!(this->checkValue<double>(value)))
		throw OperandFactory::ValueException();
	try
	{
		std::stod(value);
	}
	catch (...)
	{
		throw OperandFactory::ValueException(); 
	}
	return(new EOperand<double>(Double, DoublePrec, std::stod(value)));
}

//******************************EXCEPTIONS
OperandFactory::ValueException::ValueException()throw() : std::exception() {
	this->_errorMessage = "Error! Value is unacceptable!";
}

OperandFactory::ValueException::ValueException(std::string errorMessage)throw() : std::exception() {
	this->_errorMessage = errorMessage;
}

OperandFactory::ValueException::~ValueException()throw() {}

OperandFactory::ValueException::ValueException(const ValueException &obj) {
	*this = obj;
	return;
}

OperandFactory::ValueException& OperandFactory::ValueException::operator=(ValueException const &obj) {
	static_cast<void>(obj);
	return (*this);
}

const char *OperandFactory::ValueException::what () const throw() {
	return this->_errorMessage.c_str();
}
