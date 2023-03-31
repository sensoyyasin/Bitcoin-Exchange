#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}

	//data.csv file check
	std::ifstream bitcoin_file("data.csv");
	if (!bitcoin_file.is_open())
	{
		std::cerr << "Couldn't read Bitcoin file" << std::endl;
		return (1);
	}

	//second arg check for example -> .csvx
	if (strcmp(argv[1], "input.txt") != 0)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	BitcoinExchange bitcoin;
	bitcoin.rateCalculator(argv[1]);
}
