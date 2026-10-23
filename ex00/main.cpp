/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:33:22 by afournie          #+#    #+#             */
/*   Updated: 2026/10/23 18:21:32 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

struct Taux {
	std::string date;
	double valeur;
};

int main() {
	std::ifstream fichier("data.csv");
	if (!fichier.is_open()) {
		std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
		return 1;
	}

	std::vector<Taux> taux;
	std::string ligne;

	std::getline(fichier, ligne);

	while (std::getline(fichier, ligne)) {
		if (ligne.empty())
			continue;

		std::istringstream ss(ligne);
		std::string date, valeurStr;

		if (!std::getline(ss, date, ',') || !std::getline(ss, valeurStr, ',')) {
			std::cerr << "Ligne ignoree : " << ligne << std::endl;
			continue;
		}

		std::istringstream conv(valeurStr);
		double valeur;
		if (!(conv >> valeur)) {
			std::cerr << "Valeur invalide : " << ligne << std::endl;
			continue;
		}

		Taux t;
		t.date = date;
		t.valeur = valeur;
		taux.push_back(t);
	}

	fichier.close();

	for (std::vector<Taux>::const_iterator it = taux.begin(); it != taux.end(); ++it) {
		std::cout << it->date << " -> " << it->valeur << std::endl;
	}

	return 0;
}
