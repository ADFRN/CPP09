/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 16:53:40 by afournie          #+#    #+#             */
/*   Updated: 2026/10/28 18:11:05 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
		return (std::cout << "Error" << std::endl, EXIT_FAILURE);

	try {
		RPN calaculator3000;
		calaculator3000.calculator(av[1]);
	} catch (...)
	{
		std::cerr << "Error" << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
