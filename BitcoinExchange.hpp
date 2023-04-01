/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysensoy <ysensoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:50:12 by ysensoy           #+#    #+#             */
/*   Updated: 2023/03/31 16:26:10 by ysensoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <ctime>
#include "string.h"
#include <cstdlib>
#include <iomanip>
#include <map>

class BitcoinExchange
{
	public:
		int curr_year;
		int curr_month;
		int curr_day;
		
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& copy);
		BitcoinExchange operator = (const BitcoinExchange& copy);
		~BitcoinExchange();

		void rateCalculator(char *filename);

		std::map<int, float> map;
		std::ifstream ifs;
};

#endif