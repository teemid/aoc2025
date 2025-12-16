#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <algorithm>
#include <unordered_set>


struct TeleportationLab
{
    std::vector<std::vector<char>> tachyon_manifolds;
};

void print(const TeleportationLab &lab);
int64_t part1(TeleportationLab &lab);
uint64_t part2(TeleportationLab &lab);

int main(int argc, char *argv[])
{
    std::string filename(argv[1]);

    std::ifstream fs(filename);

    TeleportationLab lab;

    std::string line;
    while (std::getline(fs, line))
    {
        std::istringstream iss(line);

        std::vector<char> l;
        char c;
        while (iss >> c)
        {
            l.push_back(c);
        }

        lab.tachyon_manifolds.push_back(l);
    }

    uint64_t count = part2(lab);

    return 0;
}

void print(const TeleportationLab &lab)
{
    for (const std::vector<char> &line : lab.tachyon_manifolds)
    {
        for (char c : line)
        {
            std::cout << c;
        }

        std::cout << std::endl;
    }
}

int find_start_position(const TeleportationLab &lab)
{
    for (int i = 0; i < lab.tachyon_manifolds.size(); i++)
    {
        if (lab.tachyon_manifolds[0][i] == 'S')
        {
            return i;
        }
    }

    return -1;
}

int64_t part1(TeleportationLab &lab)
{
    int64_t split_count = 0;

    int x = find_start_position(lab);

    std::unordered_set<int> tachyon_beams = { x };
    std::unordered_set<int> next_tachyon_beams = {};

    for (int y = 1; y < lab.tachyon_manifolds.size(); y++)
    {
        std::vector<char> &line = lab.tachyon_manifolds[y]; 
        for (int tachyon_beam : tachyon_beams)
        {
            char c = line[tachyon_beam];
            switch (c)
            {
                case '.':
                {
                    line[tachyon_beam] = '|';

                    next_tachyon_beams.insert(tachyon_beam);
                } break;
                case '^':
                {
                    split_count += 1;

                    next_tachyon_beams.insert(tachyon_beam - 1);
                    next_tachyon_beams.insert(tachyon_beam + 1);
                } break;
            }
        }

        std::swap(tachyon_beams, next_tachyon_beams);
        next_tachyon_beams.clear();

#ifdef AOC_DEBUG
        print(lab);

        std::cout << std::endl;
#endif
    }

    std::cout << "The tachyon beam is split a total of " << split_count << " times." << std::endl;

    return split_count;
}

uint64_t sum(const std::vector<uint64_t> &beam_counts)
{
    uint64_t sum = 0;
    for (uint64_t beam_count : beam_counts)
    {
        sum += beam_count;
    }

    return sum;
}

void print(const std::vector<uint64_t> &beam_counts)
{
    for (uint64_t beam_count : beam_counts)
    {
        std::cout << std::setw(3) << beam_count << " ";
    }

    std::cout << "\t" << sum(beam_counts);
    // std::cout << "\t" << std::accumulate(beam_counts.begin(), beam_counts.end(), int64_t(0));

    std::cout << std::endl;
}

uint64_t part2(TeleportationLab &lab)
{
    std::vector<uint64_t> counts(lab.tachyon_manifolds[0].size(), 0);

    int x_start = find_start_position(lab);

    counts[x_start] = 1;

    for (int y = 1; y < lab.tachyon_manifolds.size(); y++)
    {
#ifdef AOC_DEBUG
        print(counts);
#endif

        std::vector<char> &line = lab.tachyon_manifolds[y];
        for (int x = 0; x < line.size(); x++)
        {
            char c = line[x];
            switch (c)
            {
                case '^':
                {
                    counts[x - 1] += counts[x];
                    counts[x + 1] += counts[x];

                    counts[x] = 0;
                } break;
            }
        }
    }

#ifdef AOC_DEBUG
    print(counts);
#endif

    std::cout << "The particle ends up on " << sum(counts) << " different timelines." << std::endl;

    return sum(counts);
}
