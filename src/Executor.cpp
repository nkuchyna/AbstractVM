/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 20:56:16 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/12/07 20:56:18 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Executor.hpp"
#include "NewStack.cpp"
#include <algorithm>

Executor::Executor(Token &token) : _token(token){

	actions[0] = &Executor::pop;
	actions[1] = &Executor::dump;
	actions[2] = &Executor::assert;
	actions[3] = &Executor::add;
	actions[4] = &Executor::sub;
	actions[5] = &Executor::mul;
	actions[6] = &Executor::div;
	actions[7] = &Executor::mod;
	actions[8] = &Executor::print;
	actions[9] = &Executor::push;
	actions[10] = &Executor::equal;
	actions[11] = &Executor::compare;
	actions[12] = &Executor::square;
	actions[13] = &Executor::clear;
	actions[14] = &Executor::min;
	actions[15] = &Executor::max;

	this->_operandFactory = new OperandFactory();
}

Executor::~Executor() {
	NewStack<const IOperand*>::iterator it = _myStack.begin();
	NewStack<const IOperand*>::iterator ite = _myStack.end();
	while (it++ != ite) 
		delete *it;
	delete this->_operandFactory;
}

Executor& Executor::operator=(const Executor &obj) {
	if (this != &obj)
	{
		this->_token = obj._token;
		this->_myStack = obj._myStack;
		this->_operandFactory = new OperandFactory(*obj._operandFactory);
	}
	return(*this);
}

int	Executor::tokenProcessing() {

	switch (this->_token.getInstructionType()) {
		case Exit:
			return (0);
		case DefaultInstuctionType :
			return (-1);
		default:
			this->instructionsExecution();
	}
	return (1);
}

//****************INSTRUCTION*********************************
void	Executor::push() {
	this->_myStack.push(_operandFactory->createOperand(_token.getOperandType(), _token.getOperandValue()));
}

void Executor::pop() {

	if (_myStack.size() < 1)
		throw Executor::PopOnEmptyStack();
	this->_myStack.pop();
}

void Executor::dump() {

	if (_myStack.size() < 1)
		return;
	NewStack<const IOperand*>::iterator it = _myStack.begin();
	NewStack<const IOperand*>::iterator ite = _myStack.end();
	while (--ite != (it - 1))
		std::cout << BLUE_COLOR << (*ite)->toString() << END_COLOR << std::endl;
}

void Executor::assert() {

	if (_myStack.size() < 1)
		throw Executor::TooFewValuesOnStack();
	const IOperand	*operand = this->_myStack.top();
	if (!(_myStack.size() > 0 && std::stod(operand->toString()) == std::stod(this->_token.getOperandValue())
	&& operand->getType() == this->_token.getOperandType()))
		throw Executor::NotAppropriateParameterException();
}

void Executor::add() {

	if(_myStack.size() < 2)
		throw Executor::TooFewValuesOnStack();
	const IOperand* firstOperand = _myStack.top();
	this->_myStack.pop();
	const IOperand* secondOperand = _myStack.top();
	this->_myStack.pop();
	const IOperand* result = *secondOperand + *firstOperand;
	this->_myStack.push(result);
	delete firstOperand;
	delete secondOperand;
}

void Executor::sub() {

	if(_myStack.size() < 2)
		throw Executor::TooFewValuesOnStack();
	const IOperand* firstOperand = _myStack.top();
	this->_myStack.pop();
	const IOperand* secondOperand = _myStack.top();
	this->_myStack.pop();
	const IOperand* result = *secondOperand - *firstOperand;
	this->_myStack.push(result);
	delete firstOperand;
	delete secondOperand;
}

void Executor::mul() {

	if(_myStack.size() < 2)
		throw Executor::TooFewValuesOnStack();
	const IOperand* firstOperand = _myStack.top();
	this->_myStack.pop();
	const IOperand* secondOperand = _myStack.top();
	this->_myStack.pop();
	const IOperand* result = *firstOperand * (*secondOperand);
	this->_myStack.push(result);
	delete firstOperand;
	delete secondOperand;
}

void Executor::div() {

	if(_myStack.size() < 2)
		throw Executor::TooFewValuesOnStack();
	const IOperand* secondOperand = _myStack.top();
	this->_myStack.pop();
	const IOperand* firstOperand = _myStack.top();
	if (std::stod(secondOperand->toString()) == 0)
	{
		this->_myStack.push(secondOperand);
		throw Executor::ZeroDivisiorException();
	}
	this->_myStack.pop();
	const IOperand* result = *firstOperand / (*secondOperand);
	this->_myStack.push(result);
	delete firstOperand;
	delete secondOperand;
}

void Executor::mod() {
	if(_myStack.size() < 2)
		throw Executor::TooFewValuesOnStack();
	const IOperand* secondOperand = _myStack.top();
	this->_myStack.pop();
	const IOperand* firstOperand = _myStack.top();
	if (std::stoi(secondOperand->toString()) == 0)
	{
		this->_myStack.push(secondOperand);
		throw Executor::ZeroDivisiorException();
	}
	this->_myStack.pop();
	const IOperand* result =  *firstOperand % (*secondOperand);
	this->_myStack.push(result);
	delete firstOperand;
	delete secondOperand;
}

void Executor::print() {

	if (_myStack.size() < 1)
		throw Executor::TooFewValuesOnStack();
	const IOperand	*operand = this->_myStack.top();
	if (operand->getType() != Int8)
		throw Executor::NotAppropriateParameterException();
	int		ret = std::stoi(operand->toString());
	if (ret < 0)
		ret += 256;
	std::cout << YELLOW_COLOR << static_cast<char>(ret) << END_COLOR << std::endl;
}

void Executor::equal() {

	if (_myStack.size() == 0)
		throw Executor::TooFewValuesOnStack();
	const IOperand	*firstOperand = _myStack.top();
	const IOperand	*secondOperand = _operandFactory->createOperand(this->_token.getOperandType(), this->_token.getOperandValue());
	if (*secondOperand != *firstOperand)
		std::cout << YELLOW_COLOR << "Operand values are not equal!" << END_COLOR << std::endl;
	else
		std::cout << YELLOW_COLOR << "Operand values are equal!" << END_COLOR << std::endl;
	delete secondOperand;
}

void Executor::compare() {

	if(_myStack.size() < 2)
		throw Executor::TooFewValuesOnStack();
	const IOperand *secondOperand = _myStack.top();
	const IOperand *firstOperand = *(_myStack.end() - 2);
	
	if (!(*secondOperand > (*firstOperand)) && *firstOperand != (*secondOperand))
		std::cout << YELLOW_COLOR << "Second operand value is less!" << END_COLOR << std::endl;
	else if (*secondOperand > (*firstOperand) && *firstOperand != (*secondOperand))
		std::cout << YELLOW_COLOR << "Second operand value is bigger!" << END_COLOR << std::endl;
	else
		std::cout << YELLOW_COLOR << "Operand values are equal!" << END_COLOR << std::endl;
}

void Executor::square() {

	if(_myStack.size() < 1)
		throw Executor::TooFewValuesOnStack();
	const IOperand* firstOperand = _myStack.top();
	const IOperand* secondOperand = _operandFactory->createOperand(firstOperand->getType(), firstOperand->toString());
	this->_myStack.pop();
	const IOperand* result = *firstOperand * (*secondOperand);
	this->_myStack.push(result);
	delete firstOperand;
	delete secondOperand;
}

void Executor::clear() {

	if(_myStack.size() < 1)
		throw Executor::TooFewValuesOnStack();
	NewStack<const IOperand*>::iterator it = _myStack.begin();
	NewStack<const IOperand*>::iterator ite = _myStack.end();
	while (--ite != (it - 1))
	{
		delete *ite;
		_myStack.pop();
	}
	std::cout << YELLOW_COLOR << "The stack was cleared!" << END_COLOR << std::endl;
}

void Executor::min() {

	if(_myStack.size() < 1)
		throw Executor::TooFewValuesOnStack();
	NewStack<const IOperand*>::iterator it = _myStack.begin();
	NewStack<const IOperand*>::iterator ite = _myStack.end() - 1;
	double		min_value = std::stod((*ite)->toString());
	while (--ite != (it - 1))
	{
		min_value = std::min(min_value, std::stod((*ite)->toString()));
	}
	std::cout << YELLOW_COLOR << min_value << END_COLOR << std::endl;
}

void Executor::max() {

	if(_myStack.size() < 1)
		throw Executor::TooFewValuesOnStack();
	NewStack<const IOperand*>::iterator it = _myStack.begin();
	NewStack<const IOperand*>::iterator ite = _myStack.end() - 1;
	double		min_value = std::stod((*ite)->toString());
	while (--ite != (it - 1))
	{
		min_value = std::max(min_value, std::stod((*ite)->toString()));
	}
	std::cout << YELLOW_COLOR << min_value << END_COLOR << std::endl;
}

int	Executor::instructionsExecution() {
	(this->*actions[_token.getInstructionType()])();
	return (0);
}

//**********EXEPTIONS*************************************************************

Executor::PopOnEmptyStack::PopOnEmptyStack()throw() : std::exception() {}

Executor::PopOnEmptyStack::~PopOnEmptyStack()throw() {}

Executor::PopOnEmptyStack::PopOnEmptyStack(const PopOnEmptyStack &obj) {
	*this = obj;
	return;
}

Executor::PopOnEmptyStack& Executor::PopOnEmptyStack::operator=(PopOnEmptyStack const &obj) {
	static_cast<void>(obj);
	return (*this);
}

const char *Executor::PopOnEmptyStack::what () const throw() {
	return "Error! Pop on empty stack!";
}
//**********************
Executor::TooFewValuesOnStack::TooFewValuesOnStack()throw() : std::exception() {}

Executor::TooFewValuesOnStack::~TooFewValuesOnStack()throw() {}

Executor::TooFewValuesOnStack::TooFewValuesOnStack(const TooFewValuesOnStack &obj) {
	*this = obj;
	return;
}

Executor::TooFewValuesOnStack& Executor::TooFewValuesOnStack::operator=(TooFewValuesOnStack const &obj) {
	static_cast<void>(obj);
	return (*this);
}

const char *Executor::TooFewValuesOnStack::what () const throw() {
	return "Error! Too few arguments on the stack!";
}
//**********************
Executor::ZeroDivisiorException::ZeroDivisiorException()throw() : std::exception() {}

Executor::ZeroDivisiorException::~ZeroDivisiorException()throw() {}

Executor::ZeroDivisiorException::ZeroDivisiorException(const ZeroDivisiorException &obj) {
	*this = obj;
	return;
}

Executor::ZeroDivisiorException& Executor::ZeroDivisiorException::operator=(ZeroDivisiorException const &obj) {
	static_cast<void>(obj);
	return (*this);
}

const char *Executor::ZeroDivisiorException::what () const throw() {
	return "Error! The divisor is equivalent to zero!";
}
//**********************
Executor::NotAppropriateParameterException::NotAppropriateParameterException()throw() : std::exception() {}

Executor::NotAppropriateParameterException::~NotAppropriateParameterException()throw() {}

Executor::NotAppropriateParameterException::NotAppropriateParameterException(const NotAppropriateParameterException &obj) {
	*this = obj;
	return;
}

Executor::NotAppropriateParameterException& Executor::NotAppropriateParameterException::operator=(NotAppropriateParameterException const &obj) {
	static_cast<void>(obj);
	return (*this);
}

const char *Executor::NotAppropriateParameterException::what () const throw() {
	return "Error! The parameter does not match!";
}
