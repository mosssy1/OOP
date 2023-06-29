#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "DictionaryProcessor.h"

using namespace std;


void StartConsole(Dictionary& dictionary, string fileName)
{
    string input;
    while (getline(cin, input))
    {
        if (input == "...")
        {
            break;
        }

        input = StringToLower(input);
        if (dictionary.find(input) != dictionary.end())
        {
            cout << dictionary[input] << endl;
        }
        else
        {
            cout << "Unknown word. Enter translation:" << endl;
            string translation;
            getline(cin, translation);
            translation = StringToLower(translation);
            if (!translation.empty())
            {
                dictionary[input] = translation;
            }
            else
            {
                cout << "The word \"" + input + "\" was ignored." << endl;
            }
        }
    }

    if (!dictionary.empty())
    {
        cout << "Save dictionary? (y/n)" << endl;
        string answer;
        getline(cin, answer);

        answer = StringToLower(answer);
        if (answer == "y")
        {
            if (fileName.empty())
            {
                cout << "Enter file name:" << endl;
                getline(cin, fileName);
            }
            SaveDictionary(dictionary, fileName);
        }
    }
}

int main(int argc, char* argv[])
{
    Dictionary dictionary;
    string fileName;

    if (!GetDictionary(argc, argv, dictionary, fileName))
    {
        return 0;
    }

    StartConsole(dictionary, fileName);

    return 0;
}