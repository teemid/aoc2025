#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <cassert>


enum class Op
{
    None,
    Add,
    Mult, 
};

struct HomeworkPart1
{
    std::vector<std::vector<int64_t>> rows;
    std::vector<Op> ops;
};

struct HomeworkPart2
{
    std::vector<int64_t> columns;
    std::vector<Op> ops;
};

void parse_part1(std::ifstream &fs, HomeworkPart1 &homework);
void parse_part2(std::ifstream &fs, HomeworkPart2 &homework);
void print(const HomeworkPart1 &homework);
int64_t part1(const HomeworkPart1 &homework);
int64_t part2(const HomeworkPart2 &homework);

int main(int argc, char *argv[])
{
    std::string filename(argv[1]);

    std::ifstream fs(filename);

    HomeworkPart2 homework;
    parse_part2(fs, homework);
    int64_t total = part2(homework);

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
            default: { assert(false); } break;
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
            case Op::None:
            {
                assert(false);
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

void parse_part2(std::ifstream &fs, HomeworkPart2 &homework)
{
    std::string line;
    std::vector<char> operations;
    std::vector<std::string> columns;
    while (std::getline(fs, line))
    {
        if (operations.size() == 0)
        {
            operations.resize(line.size(), ' ');
            columns.resize(line.size());
        }

        for (int column = 0; column < line.size(); column++)
        {
            char c = line[column];
            switch (c)
            {
                case ' ': continue;
                case '+':
                case '*':
                {
                    operations[column] = c;
                } break;
                default:
                {
                    std::string &s = columns[column];
                    s.push_back(c);
                }
            }
        }
    }

    homework.ops.resize(columns.size());
    homework.columns.resize(columns.size());

    for (int i = 0; i < columns.size(); i++)
    {
        const std::string &column = columns[i];

        std::istringstream iss(column);
        int64_t value = 0;

        iss >> value;

        homework.columns[i] = value;
        
        switch (operations[i])
        {
            case ' ': { homework.ops[i] = Op::None; } break;
            case '+': { homework.ops[i] = Op::Add; } break;
            case '*': { homework.ops[i] = Op::Mult; } break;
            default: { assert(false); } break;
        }
    }
}

int64_t part2(const HomeworkPart2 &homework)
{
    int64_t total = 0;

    std::vector<int64_t> operands;
    for (int column = homework.columns.size() - 1; column >= 0; column--)
    {
        switch (homework.ops[column])
        {
            case Op::None: { operands.push_back(homework.columns[column]); } break;
            case Op::Add:
            {
                operands.push_back(homework.columns[column]);

                int64_t sum = 0;
                for (int64_t operand : operands)
                {
                    sum += operand;
                }

                total += sum;

                operands.clear();

                column--;
            } break;
            case Op::Mult:
            {
                operands.push_back(homework.columns[column]);

                int64_t prod = 1;
                for (int64_t operand : operands)
                {
                    prod *= operand;
                }

                total += prod;

                operands.clear();

                column--;
            } break;
        }
    }

    return total;
}

