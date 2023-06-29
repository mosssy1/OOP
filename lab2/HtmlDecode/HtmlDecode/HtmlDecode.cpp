
#include <iostream>
#include <string>
#include <map>
#include "HtmlDecodeProcessor.h"

using namespace std;


bool HtmlDecode(istream& input, ostream& output)
{
	try
	{
		string line;
		while (getline(input, line))
		{
			output << HtmlDecode(line) << endl;
		}
		return true;
	}
	catch (exception e)
	{
		return false;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 1)
	{
		cout << "Invalid arguments count" << endl;
		cout << "Use: HtmlDecode.exe" << endl;
		return 1;
	}

	if (!HtmlDecode(cin, cout))
	{
		cout << "Something goes wrong";
		return 1;
	}

	return 0;
}
