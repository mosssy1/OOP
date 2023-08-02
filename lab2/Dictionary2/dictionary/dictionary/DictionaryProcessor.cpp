#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "DictionaryProcessor.h"



std::string StringToLower(std::string& s)
{
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return tolower(c); }
    );
    return s;
}

void LoadWordWithTranslationToDictionary(Dictionary& dictionary, std::string& line)
{
    std::string key;
    std::string value;
    line = StringToLower(line);
    std::istringstream stream(line);
    char temp;

    stream >> key;
    while (stream.peek() != EOF)
    {
        stream >> temp;
        value += temp;
        if (temp == ',')
        {
            value += ' ';
        }
    }
    dictionary[key] = value;
}

void LoadDictionary(Dictionary& dictionary, const std::string& fileName)
{
    std::ifstream file(fileName);
    std::string line;
    while (std::getline(file, line))
    {
        LoadWordWithTranslationToDictionary(dictionary, line);
    }
}

bool GetDictionary(int argc, char* argv[], Dictionary& dictionary, std::string& fileName)
{
    if (argc == 1)
    {
        fileName = "dictionary.txt";
    }
    else if (argc == 2)
    {
        fileName = argv[1];
    }
    else
    {
        std::cout << "Invalid arguments count" << std::endl;
        return false;
    }

    LoadDictionary(dictionary, fileName);
    return true;
}

void SaveDictionary(Dictionary& dictionary, std::string& fileName)
{
    std::ofstream file(fileName);
    for (auto const& item : dictionary)
    {
        file << item.first << " " << item.second << std::endl;
    }
}

