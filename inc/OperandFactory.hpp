/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 13:54:08 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/22 13:54:10 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP
#include "AbstractVM.hpp"
#include "IOperand.hpp"

class OperandFactory {

public:
	OperandFactory();
	~OperandFactory();
	OperandFactory(const OperandFactory &obj);
	OperandFactory& operator=(OperandFactory const &obj);

	IOperand const *(OperandFactory::*actions[5])(std::string const & value) const;
	IOperand const * createOperand(eOperandType type, std::string const & value) const;
	template <typename T>
	bool	checkValue(const std::string value) const;
	void	checkIntValue(double value, eOperandType type) const;

private:
	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;

class ValueException : public std::exception {
	std::string		_errorMessage;
	public:
		ValueException()throw();
		ValueException(std::string errorMessage)throw();
		virtual ~ValueException()throw();
		ValueException(const ValueException &obj);
		ValueException& operator=(ValueException const &obj);
		virtual const char *what() const throw(); 
	};
};

#endif
