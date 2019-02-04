/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eOperand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 13:31:55 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/23 13:03:55 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EOPERAND_HPP
#define EOPERAND_HPP
#include "AbstractVM.hpp"
#include "IOperand.hpp"
#include "OperandFactory.hpp"

template <typename T>

class EOperand : public IOperand{

private:
	eOperandType 			_type;
	int						_precision;
	T						_rawValue;
	std::string				_strValue;
	const OperandFactory	_operandFactory;

public:
	EOperand();
	EOperand(eOperandType type, int precision, T rawValue);
	~EOperand();
	EOperand(const EOperand<T> &obj);
	EOperand<T>& operator=(const EOperand<T> &obj);

	int getPrecision(void) const;
	eOperandType getType(void) const;
	
	IOperand const * operator+(IOperand const &rhs) const;
	IOperand const * operator-(IOperand const &rhs) const;
	IOperand const * operator*(IOperand const &rhs) const;
	IOperand const * operator/(IOperand const &rhs) const;
	IOperand const * operator%(IOperand const &rhs) const;
	bool	operator!=(IOperand const &rhs) const;
	bool	operator>(IOperand const &rhs) const;
	std::string const &toString(void) const;
};

#endif
