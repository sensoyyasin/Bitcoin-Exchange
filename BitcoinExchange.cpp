/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysensoy <ysensoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:50:12 by ysensoy           #+#    #+#             */
/*   Updated: 2023/03/31 17:18:20 by ysensoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/* Strtok examples:
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] ="- This, a sample string.";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str," ,.-");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
  }
  return 0;
}

Output : 
Splitting string "- This, a sample string." into tokens:
This
a
sample
string
 */

BitcoinExchange::BitcoinExchange()
{
	std::string line;
	char *ptr;
	float rate;
	int curr_stamp;

	this->curr_day = 0;
	this->curr_month = 0;
	this->curr_year = 0;
	this->ifs.open("data.csv", std::ifstream::in);
	if (!this->ifs.is_open())
		std::cout << "File could not open!" << std::endl;

	std::getline(this->ifs, line);
	
	while(std::getline(this->ifs, line))
	{
		ptr = strtok((char *)(line.c_str()), "-,"); //line parsing with strtok.
		this->curr_year = atoi(ptr); //year finding from .csv
		this->curr_month = atoi(strtok(NULL, "-,"));
		this->curr_day = atoi(strtok(NULL, "-,"));
		rate = atof(strtok(NULL, "-,"));

		curr_stamp = this->curr_year * 100 + this->curr_month * 10 + this->curr_day;
		//curr_stamp = (this->curr_year << 16) + (this->curr_month << 8) + (this->curr_day); // unique value
		this->map.insert(std::pair<int, float>(curr_stamp, rate));
	}
}

BitcoinExchange::~BitcoinExchange()
{
	this->ifs.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy)
{
	*this = copy;
}

BitcoinExchange BitcoinExchange::operator = (BitcoinExchange const&)
{
	return (*this);
}

void BitcoinExchange::rateCalculator(char *filename)
{
	std::ifstream ifn;
	std::string line;
	std::string temp;
	char *ptr;
	float rate;
	int curr_stamp;
	this->curr_day = 0;
	this->curr_month = 0;
	this->curr_year = 0;

	ifn.open(filename, std::ifstream::in);
	if (!ifn.is_open())
	{
		std::cout << "Error: could not open file." << std::endl;
		return;
	}
	
	std::getline(ifn, line);
	while(std::getline(ifn, line))
	{
		if (!strchr(line.c_str(), '|') || !strchr(line.c_str(), '-'))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		temp = line;
		ptr = strtok((char *)(line.c_str()), "-|"); //const char to char
		this->curr_year = atoi(ptr);
		if (this->curr_year < 2000 || this->curr_year > 2023)
		{
			std::cout << "Error: invalid year => " << temp << std::endl;
			continue;
		}
		this->curr_month = atoi(strtok(NULL, "-|"));
		if (this->curr_month < 1 || this->curr_month > 12)
		{
			std::cout << "Error: invalid month => " << temp << std::endl;
			continue;
		}
		this->curr_day = atoi(strtok(NULL, "-|"));
		if (this->curr_day  < 1 || this->curr_day  > 31)
		{
			std::cout << "Error: invalid day => " << temp << std::endl;
			continue;
		}
		rate = atof(strtok(NULL, "|"));
		if (rate < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		else if (rate > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		curr_stamp = this->curr_year * 100 + this->curr_month * 10 + this->curr_day;
		//curr_stamp = (this->curr_year << 16) + (this->curr_month << 8) + (this->curr_day);
		for (std::map<int, float>::iterator it = this->map.begin(); it != map.end(); it++)
		{
			if (it->first == curr_stamp)
			{
				std::cout << temp.substr(0, 10) << " => " << temp.substr(13, temp.size() - 13) << " = " << it->second * rate << std::endl;
				break;
			}
			else if (it->first > curr_stamp)
			{
				std::cout << temp.substr(0, 10) << " => " << temp.substr(13, temp.size() - 13) << " = " << (--it)->second * rate << std::endl;
				break;
			}
		}
	}
	ifn.close();
}