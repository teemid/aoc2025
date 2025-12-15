#include <iostream>
#include <fstream>
#include <vector>
#include <string>


struct Rotation
{
    enum Direction
    {
        Left,
        Right,
    };

    Direction dir;
    int rot;
};

int part1(const std::vector<Rotation> &rotations);
int part2(const std::vector<Rotation> &rotations);

int main(int argc, char *argv[])
{
    std::string filename(argv[1]);
    
    std::ifstream fs(filename);

    char dir;
    std::vector<Rotation> rotations;
    while (fs >> dir)
    {
        int rot;
        fs >> rot;

        Rotation::Direction d;
        switch (dir)
        {
            case 'L': d = Rotation::Left; break;
            case 'R': d = Rotation::Right; break;
        }
        
        rotations.push_back({ d, rot });
    }

    int count = part2(rotations);

    std::cout << "The password is " << count << std::endl;

    return 0;
}

int part1(const std::vector<Rotation> &rotations)
{
    int count = 0;
    int dial = 50;

    for (const Rotation &r : rotations)
    {
        switch (r.dir)
        {
            case Rotation::Left:
            {
                dial -= r.rot;
            } break;
            case Rotation::Right:
            {
                dial += r.rot;
            } break;
        }

        dial %= 100;

        if (dial == 0)
        {
            count++;
        }
    }

    return count;
}

int part2(const std::vector<Rotation> &rotations)
{
    int count = 0;
    int dial = 50;

#ifdef AOC_DEBUG
    std::cout << "- The dial starts by pointing at 50" << std::endl;
#endif

    for (const Rotation &r : rotations)
    {
        switch (r.dir)
        {
            case Rotation::Left:
            {
                int pointsAtZero = (r.rot / 100);

                int remainderOfRotation = r.rot % 100;
                int newPosition = dial - remainderOfRotation;

                if (newPosition < 0)
                {
                    if (dial != 0)
                    {
                        pointsAtZero++;
                    }

                    dial = 100 + newPosition; // NOTE: newPosition is negative in this case
                }
                else
                {
                    dial = newPosition;
                    if (dial == 0)
                    {
                        pointsAtZero++;
                    }
                }

#ifdef AOC_DEBUG
                std::cout << "- The dial is rotated L"
                          << r.rot
                          << " to point at "
                          << dial
                          << "; during this rotation, it points to 0 "
                          << pointsAtZero
                          << " times."
                          << std::endl;
#endif

                count += pointsAtZero;
            } break;
            case Rotation::Right:
            {
                int pointsAtZero = (r.rot / 100);

                int remainderOfRotation = r.rot % 100;
                int newPosition = dial + remainderOfRotation;

                if (newPosition > 99)
                {
                    if (dial != 0)
                    {
                        pointsAtZero++;
                    }

                    dial = newPosition % 100;
                }
                else
                {
                    dial = newPosition;
                    if (dial == 0)
                    {
                        pointsAtZero++;
                    }
                }

#ifdef AOC_DEBUG
                std::cout << "- The dial is rotated R"
                          << r.rot
                          << " to point at "
                          << dial
                          << "; during this rotation, it points to 0 "
                          << pointsAtZero
                          << " times."
                          << std::endl;
#endif

                count += pointsAtZero;
            } break;
        }
    }

    return count;
}

