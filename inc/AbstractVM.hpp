/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:59:44 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/23 15:59:46 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM
#define ABSTRACTVM

#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <array>
#include <map>
#include <tuple>
#include <vector>
#include <cstdint>
#include <string>

#define		FILE 		1
#define		CIN			2

#define COMMENT_IN_THE_STREAM 2
#define END_OF_THE_CIN_STREAM -2
#define END_OF_THE_STREAM 0
#define ERROR -1
#define EMPTY_LINE 3

#define END_COLOR	 "\x1B[0m"
#define RED_COLOR	 "\x1B[31m"
#define BLUE_COLOR	 "\x1B[34m"
#define YELLOW_COLOR "\x1B[33m"

enum eInstuctionType {
	Pop = 0,
	Dump,
	Assert,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	Print,
	Push,
	Equal,
	Compare,
	Square,
	Clear,
	Min,
	Max,
	Exit,
	DefaultInstuctionType
};

enum eOperandType {
	Int8 = 0,
	Int16,
	Int32,
	Float,
	Double,
	DefaultOperandType
};

enum eOperandPrecision {
	Int8Prec = 8,
	Int16Prec = 16,
	Int32Prec = 32,
	FloatPrec = 32,
	DoublePrec = 64
};

const int	valueRanges[][2] =
{
	{-128, 127},
	{-32768, 32767},
	{-2147483648, 2147483647}
};

#endif
