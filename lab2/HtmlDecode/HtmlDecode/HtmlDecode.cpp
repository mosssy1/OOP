
#include <iostream>
#include <string>
#include <map>
#include "HtmlDecodeProcessor.h"



bool HtmlDecodeToString(std::istream& input, std::ostream& output)
{
	try
	{
		std::string line;
		while (std::getline(input, line))
		{
			output << HtmlDecode(line) << std::endl;
		}
		return true;
	}
	catch (std::exception e)
	{
		return false;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 1)
	{
		std::cout << "Invalid arguments count" << std::endl;
		std::cout << "Use: HtmlDecode.exe" << std::endl;
		return 1;
	}

	if (!HtmlDecodeToString(std::cin, std::cout))
	{
		std::cout << "Something goes wrong";
		return 1;
	}

	return 0;
}
