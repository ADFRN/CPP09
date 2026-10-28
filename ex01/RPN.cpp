/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 16:53:34 by afournie          #+#    #+#             */
/*   Updated: 2026/10/28 18:10:54 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(RPN const &ref) { *this = ref; }

RPN	&RPN::operator=(RPN const &ref)
{
	if (this != &ref)
		this->_data = ref._data;
	return (*this);
}

RPN::~RPN() {}

static bool isOperator(const std::string &token)
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

static int applyOperation(char token, int nb1, int nb2)
{
	switch (token)
	{
		case '+' : return nb1 + nb2;
		case '-' : return nb1 - nb2;
		case '*' : return nb1 * nb2;
		case '/' :
			if (nb2 == 0)
			{
				std::cerr << "Error can't divide by zero" << std::endl;
				std::exit(1);
			} else
				return nb1 / nb2;
		default: return 0;
	}
}

int RPN::calculator(const std::string param)
{
	std::istringstream iss(param);
	std::string token;

	while (iss >> token)
	{
		if (isOperator(token))
		{
			if (_data.size() < 2)
				return (std::cerr << "Error" << std::endl, 1);
			int nb2 = _data.top(); _data.pop();
			int nb1 = _data.top(); _data.pop();

			int result = applyOperation(token[0], nb1, nb2);
			_data.push(result);
		} else
		{
			int nb = std::atoi(token.c_str());
			_data.push(nb);
		}
	}

	if (_data.size() == 1)
	{
		std::cout << _data.top() << std::endl;
	} else
	{
		std::cerr << "Error" << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
