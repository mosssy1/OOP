#include <iostream>
#include <fstream>
#include <optional>


using namespace std;

const string OPENING_ERROR = "Failed to open ";
const string SAVING_ERORR = "Failed to save data on disk";

struct Args
{
	string inputFileName;
	string outputFileName;
};

optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	ifstream input(args->inputFileName);
	if (!input.is_open())
	{
		cout << OPENING_ERROR << argv[1] << " for reading\n";
		return 1;
	}
	ofstream output(args->outputFileName);
	if (!output.is_open())
	{
		cout << OPENING_ERROR << argv[2] << " for writing\n";
		return 1;
	}
	char ch;
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			cout << SAVING_ERORR << endl;
			return 1;
		}
	}
	if (!output.flush()) 
	{
		cout << SAVING_ERORR << endl;
		return 1;
	}

	return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: Copyfile.exe <input file name> <output file name> \n";
		return nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;
}