#include <iostream>
#include <fstream>

#include "CharacterCount.h"
#include "Application.h"

int main(int argc, char* argv[], char* envp[])
{
	g_CharCount = new CharacterCount();
	std::string inputParam = "";
	std::string outputParam = "";
	InputType inputType = InputType::FILE;
	OutputType outputType = OutputType::CONSOLE;

	if (!ParseCommandLineArgs(argc, argv, inputParam, inputType, outputParam, outputType))
	{
		return -1;
	}

	// Read and parse input
	if (inputType == InputType::FILE)
	{
		std::ifstream input;
		input.open(inputParam, std::ios::in);
		if (input.fail())
		{
			char buffer[1024];
			strerror_s(buffer, errno);
			std::cout << "Couldn't open input file: " << buffer << std::endl;
			return -1;
		}

		std::string inputText = "";
		input >> inputText;

		g_CharCount->CountChars(reinterpret_cast<const unsigned char*>(inputText.c_str()));
	}

	std::ostringstream outputStream = g_CharCount->PrintToStream(g_CharCount->countMap);

	if (outputType == OutputType::CONSOLE)
	{
		std::cout << outputStream.str() << std::endl;
	}
	else if (outputType == OutputType::FILE)
	{
		std::ofstream output;
		output.open(outputParam, std::ios::trunc);
		if (output.fail())
		{
			char buffer[1024];
			strerror_s(buffer, errno);
			std::cout << "Couldn't open output file: " << buffer << std::endl;
			return -1;
		}

		output << outputStream.str() << std::endl;
	}

	std::cout << "Finished successfully!" << std::endl;

	delete g_CharCount;
	int ret = std::getchar();

	return 0;
}

std::string GetProgramName(std::string pathToProgram)
{
	std::string programName = "";
	std::vector<std::string> elements;
	std::istringstream f(pathToProgram);
	// Get program name from command line argument containing program path
	while (getline(f, programName, '\\'))
	{
	}

	return programName;
}

void PrintHelp(std::string pathToProgram)
{
	std::string programName = GetProgramName(pathToProgram);

	std::cout << "CharCounter usage:" << std::endl;
	std::cout << "\t* -input : The following argument(s) specify the input type" << std::endl;
	std::cout << "\t*\t-f   : The following argument specifies the path to an input file" << std::endl;
	std::cout << "\t*\t-url : The following argument specifies the URL to a text document for input" << std::endl;
	std::cout << "\t*\tcb   : Take input from the clip board" << std::endl;
	std::cout << "\t* -output : The following argument(s) specifies the output type" << std::endl;
	std::cout << "\t*\tpc : Print output to the console" << std::endl;
	std::cout << "\t*\t-f : The following argument specifies the path to an output file" << std::endl;
	std::cout << "\t*" << std::endl;
	std::cout << "\t* Examples: " << std::endl;
	std::cout << "\t- .\\" << programName << " -input -f C:/Path/To/Input.txt" << std::endl;
	std::cout << "\t- .\\" << programName << " -input -f C:/Path/To/Input.txt -output -f C:/Path/To/Output.txt" << std::endl;
	std::cout << "\t- .\\" << programName << " -output pc -input cb" << std::endl;

	int ret = std::getchar();
}

bool ParseCommandLineArgs(int argc, char* argv[], std::string& inputParam, InputType& inputType, std::string& outputParam, OutputType& outputType)
{
	std::vector<std::string> arguments;

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
	std::vector<std::string>::iterator inputPosition = std::find(arguments.begin(), arguments.end(), "-input");
	std::vector<std::string>::iterator outputPosition = std::find(arguments.begin(), arguments.end(), "-output");
	if (inputPosition == arguments.end())
	{
		std::cout << "No input type specified!" << std::endl;
		PrintHelp(GetProgramName(arguments[0]));
		return false;
	}
	else
	{
		unsigned int inputIndex = std::distance(arguments.begin(), inputPosition);

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
			std::cout << "Couldn't parse input parameters!" << std::endl;
			PrintHelp(GetProgramName(arguments[0]));
			return false;
		}
		else
		{
			std::cout << "Not enough input parameters!" << std::endl;
			PrintHelp(GetProgramName(arguments[0]));
			return false;
		}
			
		// If no output is specified, it isn't fatal. Default will be Console
		if (outputPosition == arguments.end())
		{
			return true;
		}

		// Otherwise start parsing output parameters
		unsigned int outputIndex = std::distance(arguments.begin(), outputPosition);

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
			std::cout << "Unknown output type \"" << arguments[outputIndex + 1] << "!" << std::endl;
			PrintHelp(GetProgramName(arguments[0]));
			return false;
		}
		else
		{
			std::cout << "Not enough output parameters!" << std::endl;
			PrintHelp(GetProgramName(arguments[0]));
			return false;
		}

		return true;
	}
}