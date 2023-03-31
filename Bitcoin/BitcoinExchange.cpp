#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::string line;
	char *ptr;
	float rate;
	int parse_year;
	int parse_month;
	int parse_day;
	int curr_stamp;

	std::getline(this->ifs, line);
	while (std::getline(this->ifs, line))
	{
		ptr = strtok((char *)(line.c_str()), "-,");
		parse_year = atoi(ptr);
		parse_month = atoi(strtok(NULL, "-,"));
		parse_day = atoi(strtok(NULL, "-,"));
		rate = atof(strtok(NULL, "-,"));

		curr_stamp = (parse_year << 16) + (parse_month << 8) + parse_day;

		this->map.insert(std::pair<int , float>(curr_stamp, rate));
	}
}

BitcoinExchange::~BitcoinExchange()
{
	this->ifs.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	*this = copy;
}

BitcoinExchange BitcoinExchange::operator=(BitcoinExchange const &other) const
{
	return(other);
}

void	BitcoinExchange::rateCalculator(char *filename)
{
	std::ifstream ifn;
	std::string line;
	std::string temp;
	char *ptr;
	float rate;
	int parse_year;
	int parse_month;
	int parse_day;
	int curr_stamp;

	ifn.open(filename, std::ifstream::in);
	if (!ifn.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	while (std::getline(ifn, line))
	{
		if (!strchr(line.c_str(), '|') || !strchr(line.c_str(), '-'))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		temp = line;
		ptr = strtok((char *)(line.c_str()), "-|");
		parse_year = atoi(ptr);
		if (parse_year < 2000 || parse_year > 2023)
		{
			std::cerr << "Error: invalid year => " << temp << std::endl;
			continue;
		}
		parse_month = atoi(strtok(NULL, "-|"));
		if (parse_month < 1 || parse_month > 12)
		{
			std::cerr << "Error: invalid month => " << temp << std::endl;
			continue;
		}
		parse_day = atoi(strtok(NULL, "-|"));
		if (parse_day < 1 || parse_day > 31)
		{
			std::cerr << "Error: invalid day => " << temp << std::endl;
			continue;
		}
		rate = atof(strtok(NULL, "|"));
		if (rate < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		else if (rate > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}
		curr_stamp = (parse_year << 16) + (parse_month << 8) + (parse_day);
		(void)curr_stamp;
		std::map<int, float>::iterator it;

		it = this->map.begin();
		while (it != this->map.end())
		{
			if (it->first == curr_stamp)
			{
				std::cout << temp.substr(0, 10) << " => " << temp.substr(13, temp.size() - 13) << " = " << (*it).second * rate << std::endl;
				break;
			}
			else if (it->first > curr_stamp)
			{
				std::cout << temp.substr(0,10) << " => " << temp.substr(13, temp.size() - 13) << " = " << (*(--it)).second * rate << std::endl;
				break;
			}
			++it;
		}
	}
	ifn.close();
}
