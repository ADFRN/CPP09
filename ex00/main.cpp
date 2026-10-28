/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:33:22 by afournie          #+#    #+#             */
/*   Updated: 2026/10/28 16:32:33 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>


int main(int ac, char **av)
{
	if (ac != 2)
		return (std::cerr << "Error: could not open file" << std::endl, 1);

	BitcoinExchange test;
	try {
		test.loadDatabase();
		test.processExchange(av[1]);
	} catch (...)
	{
		std::cerr << "Error: could not open file" << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
