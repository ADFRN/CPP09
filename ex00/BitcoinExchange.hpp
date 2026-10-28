/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:33:35 by afournie          #+#    #+#             */
/*   Updated: 2026/10/28 16:42:33 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>

#define DATE_LENGTH 10
#define YEAR_POSITION 4
#define MONTH_POSITION 7
#define MIN_YEAR_DIGITS 0
#define MAX_YEAR_DIGITS 4
#define MIN_MONTH_DIGITS 5
#define MAX_MONTH_DIGITS 7
#define MIN_DAY_DIGITS 8
#define MAX_DAY_DIGITS 10
#define MIN_MONTH 1
#define MAX_MONTH 12
#define MIN_DAY 1
#define MAX_DAY 31

#define YEAR_LENGTH 4
#define MONTH_LENGTH 2
#define DAY_LENGTH 2

#define FEBRUARY 2
#define APRIL 4
#define JUNE 6
#define SEPTEMBER 9
#define NOVEMBER 11

class BitcoinExchange
{
	private:
		std::map<std::string, long> _data;

	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &other);
		BitcoinExchange &operator=(BitcoinExchange const &other);
		~BitcoinExchange();

		int loadDatabase();
		int processExchange(const std::string &filename);
		float getRate(const std::string &date);
};

#endif
