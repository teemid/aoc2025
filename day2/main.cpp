#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>


struct ProductIdRange
{
    int64_t start;
    int64_t stop;
};

int64_t part1(const std::vector<ProductIdRange> &ranges);
int64_t part2(const std::vector<ProductIdRange> &ranges);

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

    int64_t sum = part2(ranges);

    std::cout << "sum = " << sum << std::endl;

    return 0;
}

int64_t part1(const std::vector<ProductIdRange> &ranges)
{
    int64_t sum = 0;
    for (const auto &range : ranges)
    {
#ifdef AOC_DEBUG
        std::cout << "Checking range: " << range.start << "-" << range.stop << std::endl;
#endif

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

bool compare(int64_t id, int parts)
{
    int exp = std::log10(id);

    int64_t e = (exp / parts) + 1;
    int64_t l = std::pow(10, e);

    int64_t a = (id % l);
    int64_t i = id;

    for (int x = 1; x < parts; x++)
    {
        i /= l;

        int64_t b = (i % l);
        if (a != b)
        {
            return false;
        }
    }

    return true;
}

int64_t part2(const std::vector<ProductIdRange> &ranges)
{
    static std::vector<int64_t> primes = { 19, 17, 13, 11, 7, 5, 3, 2 };

    int64_t sum = 0;
    for (const auto &range : ranges)
    {
#ifdef AOC_DEBUG
        std::cout << "Checking range: " << range.start << "-" << range.stop << std::endl;
#endif

        for (int64_t id = range.start; id <= range.stop; id++)
        {
            int exp = std::log10(id);
            int digits = exp + 1;
            int length = digits;

            if (length == 1)
            {
                continue;
            }

            std::vector<int> lengths = { digits };
            for (int64_t prime : primes)
            {
                if (length == 1)
                {
                    break;
                }

                int64_t multiplier = 1;
                while (length % prime == 0)
                {
                    int l = prime * multiplier;
                    if (l == digits)
                    {
                        break;
                    }

                    lengths.push_back(prime * multiplier);

                    length /= prime;

                    multiplier += 1;
                }
            }

            for (int length : lengths)
            {
                if (compare(id, length))
                {
#ifdef AOC_DEBUG
                    std::cout << id << " is invalid" << std::endl;
#endif
                    sum += id;
                    break;
                }
            }
        }
    }

    return sum;
}
