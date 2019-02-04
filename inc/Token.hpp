/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 21:08:40 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/23 21:08:42 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
#define TOKEN_HPP
#include "AbstractVM.hpp"

class Token {

private:
	static int		_lineNbr;
	eInstuctionType _instructionType;
	eOperandType 	_operandType;
	std::string 	_operandValue;

public:
	Token();
	~Token();
	Token(const Token &obj);
	Token& operator=(const Token &obj);

	eInstuctionType	getInstructionType() const;
	eOperandType	getOperandType() const;
	std::string		getOperandValue() const;
	int				getLineNbr() const;
	void			setInstructionType(const int type);
	void			setOperandType(const int type);
	void			setOperandValue(const std::string operandValue);
	void			incrementLineNbr();
};

#endif
