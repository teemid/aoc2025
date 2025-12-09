#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <cassert>


enum class Op
{
    Add,
    Mult, 
};

struct HomeworkPart1
{
    std::vector<std::vector<int64_t>> rows;
    std::vector<Op> ops;
};

void parse_part1(std::ifstream &fs, HomeworkPart1 &homework);
void print(const HomeworkPart1 &homework);
int64_t part1(const HomeworkPart1 &homework);

int main(int argc, char *argv[])
{
    std::string filename(argv[1]);

    std::ifstream fs(filename);

    HomeworkPart1 homework;
    parse_part1(fs, homework);
    int64_t total = part1(homework);

    std::cout << "total = " << total << std::endl;

    return 0;
}

void print(const HomeworkPart1 &homework)
{
    for (const std::vector<int64_t> &row : homework.rows)
    {
        for (int64_t value : row)
        {
            std::cout << value << " ";
        }

        std::cout << std::endl;
    }

    for (Op op : homework.ops)
    {
        switch (op)
        {
            case Op::Add: std::cout << "+ "; break;
            case Op::Mult: std::cout << "* "; break;
        }
    }

    std::cout << std::endl;
}


void parse_part1(std::ifstream &fs, HomeworkPart1 &homework)
{
    std::string line;
    while (std::getline(fs, line))
    {
        std::istringstream iss(line);
        char c = line[0];
        if (c == '+' || c == '*')
        {
            while (iss >> c)
            {
                switch (c)
                {
                    case '*': { homework.ops.push_back(Op::Mult); } break;
                    case '+': { homework.ops.push_back(Op::Add); } break;
                    default: { assert(false); } break;
                }
            }
        }
        else
        {
            std::vector<int64_t> row;
            int64_t value;
            while (iss >> value)
            {
                row.push_back(value);
            }

            homework.rows.push_back(row);
        }
    }
}

int64_t part1(const HomeworkPart1 &homework)
{
    std::vector<int64_t> results;
    int columns = homework.ops.size(); 
    for (int i = 0; i < columns; i++)
    {
        Op op = homework.ops[i];
        switch (op)
        {
            case Op::Add:
            {
                int64_t sum = 0;
                for (const std::vector<int64_t> &row : homework.rows)
                {
                    sum += row[i];
                }

                results.push_back(sum);
            } break;
            case Op::Mult:
            {
                int64_t sum = 1;
                for (const std::vector<int64_t> &row : homework.rows)
                {
                    sum *= row[i];
                }

                results.push_back(sum);
            } break;
        }
    }

    int64_t total = 0;
    for (int64_t value : results)
    {
        total += value;
    }

    return total;
}
