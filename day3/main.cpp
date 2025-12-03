#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


struct Bank
{
    std::vector<char> batteries;
};

int part1(std::vector<Bank> &banks);
void print(const std::vector<Bank> &banks);

int main(int argc, char *argv[])
{
    std::string filename(argv[1]);

    std::ifstream fs(filename);

    std::vector<Bank> banks;
    std::string line;
    while (std::getline(fs, line))
    {
        std::istringstream iss(line);
        Bank bank;
        char c;
        while (iss >> c)
        {
            bank.batteries.push_back(c - '0');
        }

        banks.push_back(bank);
    }

    int sum = part1(banks);

    std::cout << "Part1 sum = " << sum << std::endl;


    return 0;
}

struct Index
{
    int sum;
    int a;
    int b;
};

int part1(std::vector<Bank> &banks)
{
    int sum = 0;
    for (Bank &bank : banks)
    {
        int first = 0;
        int first_index = 0;
        for (int i = 0; i < bank.batteries.size() - 1; i++)
        {
            if (bank.batteries[i] > first)
            {
                first = bank.batteries[i];
                first_index = i;
            }
        }

        int second = 0;
        int second_index = first_index + 1;
        for (int i = first_index + 1; i < bank.batteries.size(); i++)
        {
            if (bank.batteries[i] > second)
            {
                second = bank.batteries[i];
                second_index = i;
            }
        }

        int joltage = first * 10 + second;

        sum += joltage;
    }

    return sum;
}

void print(const std::vector<Bank> &banks)
{
    for (const Bank &bank : banks)
    {
        for (char battery : bank.batteries)
        {
            std::cout << char('0' + battery) << " ";
        }

        std::cout << std::endl;
    }
}
