#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "DictionaryProcessor.h"



void StartConsole(Dictionary& dictionary, std::string fileName)
{
    std::string input;
    while (std::getline(std::cin, input))
    {
        if (input == "...")
        {
            break;
        }

        input = StringToLower(input);
        if (dictionary.find(input) != dictionary.end())
        {
            std::cout << dictionary[input] << std::endl;
        }
        else
        {
            std::cout << "Unknown word. Enter translation:" << std::endl;
            std::string translation;
            std::getline(std::cin, translation);
            translation = StringToLower(translation);
            if (!translation.empty())
            {
                dictionary[input] = translation;
            }
            else
            {
                std::cout << "The word \"" + input + "\" was ignored." << std::endl;
            }
        }
    }

    if (!dictionary.empty())
    {
        std::cout << "Save dictionary? (y/n)" << std::endl;
        std::string answer;
        std::getline(std::cin, answer);

        answer = StringToLower(answer);
        if (answer == "y")
        {
            if (fileName.empty())
            {
                std::cout << "Enter file name:" << std::endl;
                std::getline(std::cin, fileName);
            }
            SaveDictionary(dictionary, fileName);
        }
    }
}

int main(int argc, char* argv[])
{
    Dictionary dictionary;
    std::string fileName;

    if (!GetDictionary(argc, argv, dictionary, fileName))
    {
        return 0;
    }

    StartConsole(dictionary, fileName);

    return 0;
}