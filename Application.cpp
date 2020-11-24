#include <iostream>
#include <fstream>

#include "CharacterCount.h"
#include "Application.h"

using namespace std;

int main(int argc, char* argv[], char* envp[])
{
	g_CharCount = new CharacterCount();
	string inputParam = "";
	string outputParam = "";
	InputType inputType = InputType::FILE;
	OutputType outputType = OutputType::CONSOLE;

	if (!ParseCommandLineArgs(argc, argv, inputParam, inputType, outputParam, outputType))
	{
		return -1;
	}

	// Read and parse input
	if (inputType == InputType::FILE)
	{
		ifstream input;
		input.open(inputParam, ios::in);
		if (input.fail())
		{
			char buffer[1024];
			strerror_s(buffer, errno);
			cout << "Couldn't open input file: " << buffer << endl;
			return -1;
		}

		string inputText = "";
		input >> inputText;

		unsigned const char* inputBuf = reinterpret_cast<const unsigned char*>(inputText.c_str());
		g_CharCount->CountChars(inputBuf);
	}

	ostringstream outputStream = g_CharCount->PrintToStream(g_CharCount->countMap);

	if (outputType == OutputType::CONSOLE)
	{
		cout << outputStream.str() << endl;
	}
	else if (outputType == OutputType::FILE)
	{
		ofstream output;
		output.open(outputParam, ios::trunc);
		if (output.fail())
		{
			char buffer[1024];
			strerror_s(buffer, errno);
			cout << "Couldn't open output file: " << buffer << endl;
			return -1;
		}

		output << outputStream.str() << endl;
	}

	cout << "Finished successfully!" << endl;

	delete g_CharCount;
	int ret = getchar();

	return 0;
}

string GetProgramName(const string& pathToProgram)
{
	string programName = "";
	vector<string> elements;
	istringstream f(pathToProgram);
	// Get program name from command line argument containing program path
	while (getline(f, programName, '\\'))
	{
	}

	return programName;
}

void PrintHelp(const string& pathToProgram)
{
	string programName = GetProgramName(pathToProgram);

	cout << "CharCounter usage:" << endl;
	cout << "\t* -input : The following argument(s) specify the input type" << endl;
	cout << "\t*\t-f   : The following argument specifies the path to an input file" << endl;
	cout << "\t*\t-url : The following argument specifies the URL to a text document for input" << endl;
	cout << "\t*\tcb   : Take input from the clip board" << endl;
	cout << "\t* -output : The following argument(s) specifies the output type" << endl;
	cout << "\t*\tpc : Print output to the console" << endl;
	cout << "\t*\t-f : The following argument specifies the path to an output file" << endl;
	cout << "\t*" << endl;
	cout << "\t* Examples: " << endl;
	cout << "\t- .\\" << programName << " -input -f C:/Path/To/Input.txt" << endl;
	cout << "\t- .\\" << programName << " -input -f C:/Path/To/Input.txt -output -f C:/Path/To/Output.txt" << endl;
	cout << "\t- .\\" << programName << " -output pc -input cb" << endl;

	int ret = getchar();
}

bool ParseCommandLineArgs(int argc, char* argv[], string& inputParam, InputType& inputType, string& outputParam, OutputType& outputType)
{
	vector<string> arguments;

	// Collect command line arguments into vector
	for (int i = 0; i < argc; i++)
	{
		arguments.push_back(argv[i]);
	}

	if (argc == 1)
	{
		PrintHelp(GetProgramName(arguments[0]));
		return false;
	}

	// Look for input and output type
	const vector<string>::iterator inputPosition = find(arguments.begin(), arguments.end(), "-input");
	const vector<string>::iterator outputPosition = find(arguments.begin(), arguments.end(), "-output");
	if (inputPosition == arguments.end())
	{
		cout << "No input type specified!" << endl;
		PrintHelp(GetProgramName(arguments[0]));
		return false;
	}
	else
	{
		unsigned int inputIndex = distance(arguments.begin(), inputPosition);

		// Start parsing input parameters
		// First parameter should always be the input type, followed by e.g. a path
		if (inputIndex + 2 < arguments.size() && arguments[inputIndex + 1] == "-f")
		{
			inputType = InputType::FILE;
			inputParam = arguments[inputIndex + 2];
		}
		else if (inputIndex + 2 < arguments.size() && arguments[inputIndex + 1] == "-url")
		{
			inputType = InputType::URL;
			inputParam = arguments[inputIndex + 2];
		}
		else if (inputIndex + 1 < arguments.size() && arguments[inputIndex + 1] == "-cb")
		{
			inputType = InputType::CLIPBOARD;
		}
		else if (inputIndex + 1 < arguments.size())
		{
			cout << "Couldn't parse input parameters!" << endl;
			PrintHelp(GetProgramName(arguments[0]));
			return false;
		}
		else
		{
			cout << "Not enough input parameters!" << endl;
			PrintHelp(GetProgramName(arguments[0]));
			return false;
		}
			
		// If no output is specified, it isn't fatal. Default will be Console
		if (outputPosition == arguments.end())
		{
			return true;
		}

		// Otherwise start parsing output parameters
		unsigned int outputIndex = distance(arguments.begin(), outputPosition);

		if (outputIndex + 2 < arguments.size() && arguments[outputIndex + 1] == "-f")
		{
			outputType = OutputType::FILE;
			outputParam = arguments[outputIndex + 2];
		}
		else if (outputIndex + 1 < arguments.size() && arguments[outputIndex + 1] == "-p")
		{
			outputType = OutputType::CONSOLE;
		}
		else if (outputIndex + 1 < arguments.size())
		{
			cout << "Unknown output type \"" << arguments[outputIndex + 1] << "!" << endl;
			PrintHelp(GetProgramName(arguments[0]));
			return false;
		}
		else
		{
			cout << "Not enough output parameters!" << endl;
			PrintHelp(GetProgramName(arguments[0]));
			return false;
		}

		return true;
	}
}