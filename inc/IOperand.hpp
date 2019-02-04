/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 13:32:03 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/22 13:32:08 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
#define IOPERAND_HPP
#include "AbstractVM.hpp"

class IOperand {
	public:
		virtual int getPrecision(void) const = 0; // Precision of the type of the instance
		virtual eOperandType getType(void) const = 0; // Type of the instance

		virtual IOperand const * operator+(IOperand const &rhs) const = 0; // Sum
		virtual IOperand const * operator-(IOperand const &rhs) const = 0; // Difference
		virtual IOperand const * operator*(IOperand const &rhs) const = 0; // Product
		virtual IOperand const * operator/(IOperand const &rhs) const = 0; // Quotient
		virtual IOperand const * operator%(IOperand const &rhs) const = 0; // Modulo
		virtual bool	operator>(IOperand const &rhs) const = 0;
		virtual bool	operator!=(IOperand const &rhs) const = 0;
	
		virtual std::string const &toString(void) const = 0; // String representation of the instance
		virtual ~IOperand(void) {}
};

#endif
