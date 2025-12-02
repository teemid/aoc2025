#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <cstdint>


struct ProductIdRange
{
    int64_t start;
    int64_t stop;
};

int64_t part1_string_based(const std::vector<ProductIdRange> &ranges);
int64_t part1_number_based(const std::vector<ProductIdRange> &ranges);

int main(int argc, char *argv[])
{
    std::string filename(argv[1]);
    std::ifstream fs(filename);

    std::vector<ProductIdRange> ranges;
    
    char c;
    ProductIdRange range;
    while (fs >> range.start)
    {
        fs >> c; // Read '-' between the numbers
        fs >> range.stop;
        fs >> c; // Read ',' between ranges

        ranges.push_back(range);
    }

    int64_t sum = part1_string_based(ranges);

    std::cout << "sum = " << sum << std::endl;

    return 0;
}

int64_t part1_string_based(const std::vector<ProductIdRange> &ranges)
{
    int64_t sum = 0;
    for (const auto &range : ranges)
    {
        std::cout << "Checking range: " << range.start << "-" << range.stop << std::endl;

        for (int64_t i = range.start; i <= range.stop; i++)
        {
            std::string n = std::to_string(i);
            std::string_view nv(n);
            int length = n.size();

            if (length % 2 != 0)
            {
                continue;
            }

            int half_length = length / 2;
            std::string_view first = nv.substr(0, half_length);
            std::string_view second = nv.substr(half_length, half_length);

            if (first == second)
            {
                sum += i;
            }
        }
    }

    return sum;
}

int64_t part1_number_based(const std::vector<ProductIdRange> &ranges)
{
    int64_t sum = 0;
    for (const auto &range : ranges)
    {
        std::cout << "Checking range: " << range.start << "-" << range.stop << std::endl;

        for (int64_t i = range.start; i <= range.stop; i++)
        {
            int64_t exp = std::log10(i);
            if (exp % 2 == 0)
            {
                continue;
            }

            int64_t e = (exp / 2) + 1;
            int64_t l = std::pow(10, e);

            int64_t low = i % l;
            int64_t high = i / l;

            if (low == high)
            {
                sum += i;
            }
        }
    }

    return sum;
}

int64_t part2_number_based(const std::vector<ProductIdRange> &ranges)
{
    int64_t sum = 0;
    for (const auto &range : ranges)
    {
        std::cout << "Checking range: " << range.start << "-" << range.stop << std::endl;

        for (int64_t i = range.start; i <= range.stop; i++)
        {
            int64_t exp = std::log10(i);
            if (exp % 2 == 0)
            {
                continue;
            }

            int64_t e = (exp / 2) + 1;
            int64_t l = std::pow(10, e);

            int64_t low = i % l;
            int64_t high = i / l;

            if (low == high)
            {
                sum += i;
            }
        }
    }

    return sum;
}
