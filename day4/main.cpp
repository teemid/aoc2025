#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


void part1(const std::vector<std::vector<char>> &map);
void print(const std::vector<std::vector<char>> &map);

int main(int argc, char *argv[])
{
    std::string filename(argv[1]);
    std::ifstream fs(filename);

    std::vector<std::vector<char>> map;

    std::string line;
    while (std::getline(fs, line))
    {
        std::vector<char> l;
        std::istringstream iss(line);
        char c;
        while (iss >> c)
        {
            l.push_back(c);
        }

        map.push_back(l);
    }

    print(map);
    part1(map);

    return 0;
}

void part1(const std::vector<std::vector<char>> &map)
{
    std::vector<std::vector<char>> out;

    int accessible = 0;
    int height = map.size();
    for (int y = 0; y < height; y++)
    {
        const std::vector<char> &line = map[y];

        static const std::vector<char> dummy(line.size(), '.');

        out.push_back(dummy);

        const std::vector<char> &up = (y == 0) ? dummy : map[y - 1];
        const std::vector<char> &down = (y == height - 1) ? dummy : map[y + 1];

        int width = line.size();
        for (int x = 0; x < width; x++)
        {
            char c = line[x];
            switch (c)
            {
                case '.': out[y][x] = '.'; continue;
                case '@':
                {
                    int neighbors = 0;

                    if (x > 0)
                    {
                        neighbors += line[x - 1] == '@';
                        neighbors += up[x - 1] == '@';
                        neighbors += down[x - 1] == '@';
                    }

                    if (x < width - 1)
                    {
                        neighbors += up[x + 1] == '@';
                        neighbors += line[x + 1] == '@';
                        neighbors += down[x + 1] == '@';
                    }

                    neighbors += up[x] == '@';
                    neighbors += down[x] == '@';

                    // std::cout << "(" << x << ", " << y << ") = " << neighbors;
                    if (neighbors > 3)
                    {
                        out[y][x] = '@';
                    }
                    else
                    {
                        accessible++;
                        out[y][x] = 'x';
                    }
                } break;
            }
        }
    }

    print(out);

    std::cout << "Accessible rolls = " << accessible << std::endl;
}

void print(const std::vector<std::vector<char>> &map)
{
    for (const std::vector<char> &line : map)
    {
        for (char c : line)
        {
            std::cout << c;
        }

        std::cout << std::endl;
    }
}
