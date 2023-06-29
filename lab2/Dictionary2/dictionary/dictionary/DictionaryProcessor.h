#pragma once
#include <string>
#include <map>
#include <sstream>

using Dictionary = std::map<std::string, std::string>;

std::string StringToLower(std::string& s);
void LoadWordWithTranslationToDictionary(Dictionary& dictionary, std::string& line);
void LoadDictionary(Dictionary& dictionary, const std::string& fileName);
bool GetDictionary(int argc, char* argv[], Dictionary& dictionary, std::string& fileName);
void SaveDictionary(Dictionary& dictionary, std::string& fileName);

