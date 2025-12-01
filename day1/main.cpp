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

    std::cout << "The password is " << count << std::endl;

    return 0;
}

