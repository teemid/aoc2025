#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>


struct Range
{
    int64_t start;
    int64_t stop;
};

int64_t part1(const std::vector<int64_t> &available, const std::vector<Range> &fresh);

int main(int argc, char *argv[])
{
    std::string filename(argv[1]);

    std::ifstream fs(filename);

    std::vector<int64_t> available_ingredients;
    std::vector<Range> fresh_ingredients;

    bool in_available_ingredients = false;
    std::string line;
    while (std::getline(fs, line))
    {
        if (line.empty())
        {
            in_available_ingredients = true;
        }

        std::istringstream iss(line);
        if (in_available_ingredients)
        {
            int64_t available_ingredient;

            iss >> available_ingredient;

            available_ingredients.push_back(available_ingredient);
        }
        else
        {
            Range range;
            char c;

            iss >> range.start;
            iss >> c;
            iss >> range.stop;

            assert(c == '-');
    
            fresh_ingredients.push_back(range);
        }
    }

    std::cout << "Available:" << std::endl;
    for (int64_t i : available_ingredients)
    {
        std::cout << i << std::endl;
    }

    std::cout << "Fresh:" << std::endl;
    for (const Range &range : fresh_ingredients)
    {
        std::cout << range.start << "-" << range.stop << std::endl;
    }

    int64_t count = part1(available_ingredients, fresh_ingredients);

    std::cout << count << " of the available ingredient IDs are fresh" << std::endl;

    return 0;
}

bool search(const std::vector<Range> &fresh_ingredients, int64_t ingredient);
int64_t part1(const std::vector<int64_t> &available, const std::vector<Range> &fresh)
{
    int64_t count = 0;
    for (int64_t ingredient : available)
    {
        if (search(fresh, ingredient))
        {
            count++;
        }
    }

    return count;
}

bool search(const std::vector<Range> &fresh_ingredients, int64_t ingredient)
{

    for (const Range &range : fresh_ingredients)
    {
        if (range.start <= ingredient && ingredient <= range.stop)
        {
            return true;
        }
    }

    return false;
}

