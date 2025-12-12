#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <cstdint>


struct Device
{
    std::string name;
    std::vector<Device *> outputs;
};

void print(const std::unordered_map<std::string, Device*> &devices);
int64_t part1(const std::unordered_map<std::string, Device*> &devices);

Device *find_or_create(std::unordered_map<std::string, Device*> &devices, const std::string &name);

int main(int argc, char *argv[])
{
    std::string filename(argv[1]);

    std::unordered_map<std::string, Device*> devices;

    std::ifstream fs(filename);
    std::string line;
    while (std::getline(fs, line))
    {
        std::istringstream iss(line);
        std::string name;

        iss >> name;

        // remove the ':' from the first name
        name = name.substr(0, name.size() - 1);

        Device *device = find_or_create(devices, name);

        while (iss >> name)
        {
            Device *output = find_or_create(devices, name);
            device->outputs.push_back(output);
        }
    }

    int64_t count = part1(devices);

    std::cout << "In total, there are " << count << " different paths leading from you to out" << std::endl;

    return 0;
}

Device *find_or_create(std::unordered_map<std::string, Device*> &devices, const std::string &name)
{
    Device *device;
    std::unordered_map<std::string, Device*>::iterator it = devices.find(name);
    if (it == devices.end())
    {
        device = new Device();
        device->name = name;

        devices[name] = device;
    }
    else
    {
        device = it->second;
    }

    return device;
}

void print(const std::unordered_map<std::string, Device*> &devices)
{
    for (const std::unordered_map<std::string, Device *>::value_type &value : devices)
    {
        Device *device = value.second;
        std::cout << device->name << ": ";
        for (int i = 0; i < device->outputs.size(); i++)
        {
            Device *output = device->outputs[i];
            std::cout << output->name;
            if (i < device->outputs.size() - 1)
            {
                std::cout << " ";
            }
        }

        std::cout << std::endl;
    }
}

int64_t part1(const std::unordered_map<std::string, Device*> &devices)
{
    std::unordered_map<std::string, Device*>::const_iterator it = devices.find("you");
    assert(it != devices.end());

    int64_t count = 0;
    std::vector<const Device *> stack = { it->second };
    while (stack.size() > 0)
    {
        const Device *device = stack.back();
        stack.pop_back();

        if (device->name == "out")
        {
            count++;
        }

        for (const Device *output : device->outputs)
        {
            stack.push_back(output);
        }
    }

    return count;
}

