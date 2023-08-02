#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>


void PrintVectorOfFloats(const std::vector<float>& v)
{
	std::for_each(v.cbegin(), v.cend(), [](const float& elem)
		{
			std::cout << elem << " ";
		});
}

bool ParseFloatsToVector(std::istream& input, std::vector<float>& v)
{
	float value = 0.f;

	while (input >> value && !input.eof())
	{
		v.push_back(value);
	}

	if (!input.eof())
	{
		return false;
	}

	return v.size() > 0;
}

void SortVector(std::vector<float>& v)
{
	std::sort(v.begin(), v.end());
}


bool MultiplyByMin(std::vector<float>& v)
{

	std::vector<float> vCopy = v;
	float minElement = *std::min_element(vCopy.begin(), vCopy.end());

	std::transform(v.begin(), v.end(), v.begin(),
		[minElement](float& element) { return element * minElement; });

	return true;
}


