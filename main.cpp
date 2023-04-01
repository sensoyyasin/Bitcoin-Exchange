/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysensoy <ysensoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:29:02 by ysensoy           #+#    #+#             */
/*   Updated: 2023/04/01 14:29:03 by ysensoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/* input.txt deki tarihi data.csv de bulur ve input.txt'deki bitcoin sayısını data.csvdeki
o tarihteki değer ile çarpar. Eğer O tarih yoksa ondan önceki en yakın tarih için aynısını yapar. */

int main(int argc, char **argv)
{
	if (argc > 2)
	{
		std::cerr << "Arg Error" << std::endl;
		exit(1);
	}
	BitcoinExchange bit;
	bit.rateCalculator(argv[1]);
}