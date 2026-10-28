/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 12:29:58 by afournie          #+#    #+#             */
/*   Updated: 2026/10/28 16:52:01 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _data(other._data) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_data = other._data;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

static bool isValidDate(const std::string & date)
{
	if (date.size() != DATE_LENGTH || date[YEAR_POSITION] != '-' || date[MONTH_POSITION] != '-')
		return false;

	for (int i = MIN_YEAR_DIGITS; i < MAX_YEAR_DIGITS; ++i)
	{
		if (!isdigit(date[i]))
			return false;
	}

	for (int i = MIN_MONTH_DIGITS; i < MAX_MONTH_DIGITS; ++i)
	{
		if (!isdigit(date[i]))
			return false;
	}

	for (int i = MIN_DAY_DIGITS; i < MAX_DAY_DIGITS; ++i)
	{
		if (!isdigit(date[i]))
			return false;
	}

	int year = atoi(date.substr(MIN_YEAR_DIGITS, YEAR_LENGTH).c_str());
	int month = atoi(date.substr(MIN_MONTH_DIGITS, MONTH_LENGTH).c_str());
	int day = atoi(date.substr(MIN_DAY_DIGITS, DAY_LENGTH).c_str());

	if (month < MIN_MONTH || month > MAX_MONTH)
		return false;

	if (day < MIN_DAY || day > MAX_DAY)
		return false;

	// For leap years (annees bissextiles)
	if (month == FEBRUARY)
	{
		bool isLeap;
		isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

		if (day > 29 || (day == 29 && !isLeap))
			return false;
	}
	else if (month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER)
	{
		if (day > 30)
			return false;
	}

	return true;
}

static bool parseAmount(const std::string &s, double &out)
{
	if (s.empty())
		return false;
	bool dot = false, digit = false;
	std::string::size_type i = (s[0] == '-') ? 1 : 0;
	for (; i < s.size(); ++i)
	{
		if (s[i] == '.')
		{
			if (dot)
				return false;
			dot = true;
		}
		else if (std::isdigit(static_cast<unsigned char>(s[i])))
			digit = true;
		else
			return false;
	}
	if (!digit)
		return false;
	out = std::strtod(s.c_str(), NULL);
	if (out == 0)
		out = 0.0;
	return true;
}

static std::string trim(const std::string &s)
{
	std::string::size_type b = s.find_first_not_of(" \t\r");
	if (b == std::string::npos)
		return "";
	std::string::size_type e = s.find_last_not_of(" \t\r");
	return s.substr(b, e - b + 1);
}

static long fullToCents(double amount) {
	return static_cast<long>(std::floor(amount * 100.0 + 0.5));
}


int BitcoinExchange::loadDatabase()
{
	std::ifstream fichier("data.csv");
	if (!fichier.is_open())
		throw std::runtime_error("Error: could not open file.");

	std::string line, date;

	std::getline(fichier, line);
	while (std::getline(fichier, line))
	{
		if (line.empty())
			continue;
		std::istringstream ss(line);
		std::string date, valeurStr;
		double amount;
		if (!std::getline(ss, date, ',') || !std::getline(ss, valeurStr, ','))
		{
			std::cerr << "ignoree - > " << line << std::endl;
			continue;
		}
		if (!parseAmount(valeurStr, amount))
		{
			std::cerr << "Error: bad input -> " << valeurStr << std::endl;
			continue ;
		}
		this->_data[date] = fullToCents(amount);
	}
	fichier.close();
	return (EXIT_SUCCESS);
}

int BitcoinExchange::processExchange(const std::string &filename)
{
	std::ifstream fichier(filename.c_str());
	if (!fichier.is_open())
		throw std::runtime_error("Error: could not open file.");

	std::string line;
	std::getline(fichier, line);

	while (std::getline(fichier, line))
	{
		if (line.empty())
			continue;

		std::string::size_type pos = line.find('|');
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = trim(line.substr(0, pos));
		std::string valueStr = trim(line.substr(pos + 1));
		double amount;

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (!parseAmount(valueStr, amount))
		{
			std::cerr << "Error: bad input -> " << line << std::endl;
			continue ;
		}
		if (amount < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (amount > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}
		std::map<std::string, long>::const_iterator it = _data.lower_bound(date);
		if (it == _data.end() || it->first != date)
		{
			if (it == _data.begin())
			{
				std::cerr << "Error: no earlier date in database " << date << std::endl;
				continue;
			}
			--it;
		}
		double total = static_cast<double>(it->second) * amount;
		std::cout << date << " => " << amount << " = " << total / 100.00 << std::endl;
	}
	fichier.close();
	return (EXIT_SUCCESS);
}
