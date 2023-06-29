#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorOfFloats(const vector<float>& v)
{
	std::for_each(v.cbegin(), v.cend(), [](const float& elem)
		{
			cout << elem << " ";
		});
}

bool ParseFloatsToVector(istream& input, vector<float>& v)
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

	return v.size() > 0 ? true : false;
}


bool MuitiplyByMin(vector<float>& v)
{

	vector<float> vCopy = v;
	float minElement = *std::min_element(vCopy.begin(), vCopy.end());

	for (float& element : v) {
		element *= minElement;
	}
	std::sort(v.begin(), v.end());
	return true;
}

//Каждый элемент массива должен быть умножен на минимальный элемент исходного массива
//Подсказка : используйте алгоритм std::min_element.
