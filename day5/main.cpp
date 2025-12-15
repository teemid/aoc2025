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
    bool reduced;
};

int64_t part1(const std::vector<int64_t> &available, const std::vector<Range> &fresh);
int64_t part2(const std::vector<Range> &fresh);

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
            continue;
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
            range.reduced = false;
            char c;

            iss >> range.start;
            iss >> c;
            iss >> range.stop;

            assert(c == '-');

            fresh_ingredients.push_back(range);
        }
    }

#ifdef AOC_DEBUG
    std::cout << "Available:" << std::endl;
    for (const int64_t i : available_ingredients)
    {
        std::cout << i << std::endl;
    }

    std::cout << "Fresh:" << std::endl;
    for (const Range &range : fresh_ingredients)
    {
        std::cout << range.start << "-" << range.stop << std::endl;
    }
#endif

    int64_t count = part2(fresh_ingredients);

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

bool is_overlap(const Range &a, const Range &b)
{
    if (a.stop < b.start)
    {
        return false;
    }
    else if (b.stop < a.start)
    {
        return false;
    }

    return true;
}

int reduce_ranges(std::vector<Range> &ranges)
{
    int reduced_ranges = 0;
    for (int i = 0; i < ranges.size(); i++)
    {
        Range &a = ranges[i];
        for (int j = 0; j < ranges.size(); j++)
        {
            if (i == j)
            {
                continue;
            }

            const Range &b = ranges[j];
            if (!is_overlap(a, b))
            {
                continue;
            }
            else
            {
                a.start = std::min(a.start, b.start);
                a.stop = std::max(a.stop, b.stop);

                reduced_ranges += 1;

                ranges.erase(ranges.begin() + j);

                i = std::max(i - 1, 0);
                j = std::max(j - 1, 0);
            }
        }
    }

    return reduced_ranges;
}

int64_t part2(const std::vector<Range> &fresh)
{
    int64_t count = 0;

    std::vector<Range> unique_ranges;
    std::vector<Range> ranges = fresh;

    for ( ; ; )
    {
        int reduced_ranges = reduce_ranges(ranges);
#ifdef AOC_DEBUG
        std::cout << "Reduced " << reduced_ranges << " number of ranges" << std::endl;
#endif 
        if (reduced_ranges == 0)
        {
            break;
        }
    }

    for (const Range &range : ranges)
    {
        count += (range.stop - range.start) + 1;
    }

    return count;
}
