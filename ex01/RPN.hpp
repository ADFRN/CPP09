/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 16:53:37 by afournie          #+#    #+#             */
/*   Updated: 2026/10/28 18:07:56 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstdlib>

class	RPN
{
	private :
		std::stack<int> _data;

	public:
		RPN();
		RPN(RPN const &ref);
		RPN &operator=(RPN const &ref);
		~RPN();

		int calculator(const std::string param);
};

#endif
