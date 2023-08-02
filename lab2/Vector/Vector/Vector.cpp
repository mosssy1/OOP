#include "CVectorProcessor.h"

int main()
{
	std::vector<float> inputData;

	if (!ParseFloatsToVector(std::cin, inputData))
	{
		std::cout << "Incorrect input data" << std::endl;
		return 1;
	}

	if (!MultiplyByMin(inputData))
	{
		std::cout << "Something went wrong" << std::endl;
		return 1;
	}

	SortVector(inputData);

	PrintVectorOfFloats(inputData);

	return 0;
}