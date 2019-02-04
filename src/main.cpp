/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 19:13:36 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/11/22 19:13:38 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVM.hpp"
#include "Parser.hpp"

int		main(int argc, char **argv)
{
	Parser				*myParser;
	try
	{
		if (argc == 1)
		{
			myParser = new Parser();
			myParser->dataStreamProcessing();
		}
		else if (argc == 2)
		{
			myParser = new Parser(argv[1]);
			myParser->dataStreamProcessing();
		}
		else
		{
			std::cout << RED_COLOR << "usage: ./avm [file]/[]" << END_COLOR << std::endl;
			return (1);
		}
	}
	catch (std::exception& e)
	{
		std::cout<< "Unappropriate value!" << std::endl;
	}
	return (0);
}
