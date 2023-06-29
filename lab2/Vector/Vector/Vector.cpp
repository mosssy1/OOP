#include "CVectorProcessor.h"

using namespace std;

int main()
{
	vector<float> inputData;

	if (!ParseFloatsToVector(cin, inputData))
	{
		cout << "Incorrect input data" << endl;
		return 1;
	}

	if (!MuitiplyByMin(inputData))
	{
		cout << "Something went wrong" << endl;
		return 1;
	}

	std::sort(inputData.begin(), inputData.end());

	PrintVectorOfFloats(inputData);

	return 0;
}