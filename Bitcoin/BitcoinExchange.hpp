#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <iomanip>
#include <time.h>
#include <map>
#include <fstream>

class BitcoinExchange
{
public:
	std::map<int, float> map;
	std::ifstream ifs;

	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &copy);
	BitcoinExchange operator=(const BitcoinExchange &other) const;
	~BitcoinExchange();

	void	rateCalculator(char *filename);
};

#endif
