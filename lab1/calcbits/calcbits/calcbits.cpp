#include <iostream>
#include <string>
#include <optional>


int CountBits(int byte)
{
    int count = 0;
    while (byte != 0)
    {
        count += byte & 1;
        byte >>= 1;
    }
    return count;
}

struct Args
{
    std::string number;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage calcbits.exe /number/\n";
        return std::nullopt;
    }
    Args args;
    args.number = argv[1];
    return args;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }

    int byte = stoi(args->number);
    if (byte < 0 || byte > 255)
    {
        std::cout << "Incorrect input for byte. Valid range: 0-255" << std::endl;
        return 1;
    }

    int bitCount = CountBits(byte);
    std::cout << bitCount << std::endl;

    return 0;
}