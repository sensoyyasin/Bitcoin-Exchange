#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main(int argc, char **argv)
{
    //arg check
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
    std::string filename = "data.csv";
    if (filename != argv[1])
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }

    std::map<std::string, double> exchange_rates;
    std::string line;
    while (std::getline(bitcoin_file, line))
    {
        std::string str_date = line.substr(0, 10);
        double exchange_rate = 42;

        exchange_rates[str_date] = exchange_rate;
    }
    
    std::map<std::string, double>::iterator iterator;
    iterator = exchange_rates.begin();
    while (iterator != exchange_rates.end())
    {
        std::cout << iterator->first << " => " << iterator->second << std::endl;
        iterator++;
    }
    return (0);
}