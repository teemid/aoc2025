#include <iostream>
#include <fstream>
#include <cstdint>
#include <cassert>
#include <string>
#include <vector>


struct Vector2
{
    int64_t x;
    int64_t y;
};

void print(const Vector2 &v);
void print(const std::vector<Vector2> &tiles);
int64_t part1(const std::vector<Vector2> &tiles);

int main(int argc, char *argv[])
{
    std::string filename(argv[1]);


    std::ifstream fs(filename);
    
    std::vector<Vector2> tiles;

    char c;
    Vector2 v;
    while (fs >> v.x)
    {
        fs >> c;
        assert(c == ',');
        fs >> v.y;

        tiles.push_back(v);
    }

    int64_t area = part1(tiles);

    std::cout << "The largest rectangle has area = " << area << std::endl;

    return 0;
}

void print(const Vector2 &v)
{
    std::cout << v.x << "," << v.y << std::endl;
}

void print(const std::vector<Vector2> &tiles);

void print(const std::vector<Vector2> &tiles)
{
    for (const Vector2 &v : tiles)
    {
        print(v);
    }

    std::cout << std::endl;
}

int64_t part1(const std::vector<Vector2> &tiles)
{
    int64_t max = 0;
    for (int i = 0; i < tiles.size(); i++)
    {
        for (int j = 0; j < tiles.size(); j++)
        {
            if (i == j) continue;

            const Vector2 &a = tiles[i];
            const Vector2 &b = tiles[j];

            int64_t diff_x = std::abs(a.x - b.x) + 1;
            int64_t diff_y = std::abs(a.y - b.y) + 1;

            int64_t area = diff_x * diff_y;

            // std::cout << "Area between" << "(" << a.x << "," << a.y << ")" << " and " << "(" << b.x << "," << b.y << ")" << " is " << area << std::endl;

            if (area > max)
            {
                max = area;
            }
        }
    }

    return max;
}

