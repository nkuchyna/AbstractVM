/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 20:56:24 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/12/07 20:56:27 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP
#include "AbstractVM.hpp"
#include "NewStack.hpp"
#include "eOperand.hpp"
#include "Token.hpp"

class Executor
{
private:
	void							(Executor::*actions[16])();
	Token							&_token;
	NewStack<const IOperand*>		_myStack;
	const OperandFactory			*_operandFactory;

public:
	Executor(Token &token);
	~Executor();
	Executor& operator=(const Executor &obj);

	int	tokenProcessing();
	int	instructionsExecution();

	 void	push();
	 void	pop();
	 void	dump();
	 void	assert();
	 void	add();
	 void	sub();
	 void	mul();
	 void	div();
	 void	mod();
	 void	print();
	 void	equal();
	 void	compare();
	 void	square();
	 void	clear();
	 void	min();
	 void	max();

	class PopOnEmptyStack : public std::exception {
	public:
		PopOnEmptyStack()throw();
		virtual ~PopOnEmptyStack()throw();
		PopOnEmptyStack(const PopOnEmptyStack &obj);
		PopOnEmptyStack& operator=(PopOnEmptyStack const &obj);
		virtual const char *what() const throw(); 
	};

	class TooFewValuesOnStack : public std::exception {
	public:
		TooFewValuesOnStack()throw();
		virtual ~TooFewValuesOnStack()throw();
		TooFewValuesOnStack(const TooFewValuesOnStack &obj);
		TooFewValuesOnStack& operator=(TooFewValuesOnStack const &obj);
		virtual const char *what() const throw(); 
	};

	class ZeroDivisiorException : public std::exception {
	public:
		ZeroDivisiorException()throw();
		virtual ~ZeroDivisiorException()throw();
		ZeroDivisiorException(const ZeroDivisiorException &obj);
		ZeroDivisiorException& operator=(ZeroDivisiorException const &obj);
		virtual const char *what() const throw(); 
	};

	class NotAppropriateParameterException : public std::exception {
	public:
		NotAppropriateParameterException()throw();
		virtual ~NotAppropriateParameterException()throw();
		NotAppropriateParameterException(const NotAppropriateParameterException &obj);
		NotAppropriateParameterException& operator=(NotAppropriateParameterException const &obj);
		virtual const char *what() const throw(); 
	};
};

#endif
