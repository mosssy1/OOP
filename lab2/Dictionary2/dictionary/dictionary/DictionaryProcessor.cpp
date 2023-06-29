#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "DictionaryProcessor.h"

using namespace std;


string StringToLower(string& s)
{
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return tolower(c); }
    );
    return s;
}

void LoadWordWithTranslationToDictionary(Dictionary& dictionary, string& line)
{
    string key;
    string value;
    line = StringToLower(line);
    istringstream stream(line);
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

void LoadDictionary(Dictionary& dictionary, const string& fileName)
{
    ifstream file(fileName);
    string line;
    while (getline(file, line))
    {
        LoadWordWithTranslationToDictionary(dictionary, line);
    }
}

bool GetDictionary(int argc, char* argv[], Dictionary& dictionary, string& fileName)
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
        cout << "Invalid arguments count" << endl;
        return false;
    }

    LoadDictionary(dictionary, fileName);
    return true;
}

void SaveDictionary(Dictionary& dictionary, string& fileName)
{
    ofstream file(fileName);
    for (auto const& item : dictionary)
    {
        file << item.first << " " << item.second << endl;
    }
}

