#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

bool ParseFloatsToVector(std::istream& input, std::vector<float>& v);
bool MultiplyByMin(std::vector<float>& v);
void SortVector(std::vector<float>& v);
void PrintVectorOfFloats(const std::vector<float>& v);