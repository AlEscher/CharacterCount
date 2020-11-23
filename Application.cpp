#include <iostream>

#include "CharacterCount.h"
#include "Application.h"

int main(int argc, char* argv[], char* envp[])
{
	std::string inputParam = "";
	InputType inputType = InputType::FILE;

	if (argc == 1)
	{
		PrintHelp(argv[0]);
		return -1;
	}
	else
	{
		if (!ParseCommandLineArgs(argc, argv, inputParam, inputType))
		{
			return -1;
		}
		std::cout << inputParam << std::endl;
	}

	g_CharCount = new CharacterCount();
	asmCountMap = reinterpret_cast<int*>(malloc(256 * sizeof(int)));

	const char* text = "aaaabbbcccccc122333ABBCCC";
	g_CharCount->CountChars(reinterpret_cast<const unsigned char*>(text));
	// AsmCountChars(reinterpret_cast<const unsigned char*>(text));

	std::cout << g_CharCount->PrintToStream(g_CharCount->countMap).str() << std::endl;

	std::cout << g_CharCount->PrintToStream(asmCountMap).str() << std::endl;

	delete g_CharCount;
	free(asmCountMap);

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
	std::cout << "\t* -input  : The following arguments specify the input type" << std::endl;
	std::cout << "\t* -f	  : The following argument specifies the path to an input file" << std::endl;
	std::cout << "\t* -output : The following argument specifies the output type" << std::endl;
	std::cout << "\t*" << std::endl;
	std::cout << "\t* Example: " << std::endl;
	std::cout << "\t- Reads the text from Input.txt and writes the result to Output.txt (creating the output file if it doesn't exist):" << std::endl;
	std::cout << "\t- .\\" << programName << " -input -f C:/Path/To/Input.txt -output -f C:/Path/To/Output.txt" << std::endl;

	int ret = std::getchar();
}

bool ParseCommandLineArgs(int argc, char* argv[], std::string& inputFile, InputType& inputType)
{
	std::vector<std::string> arguments;

	// Collect command line arguments into vector
	for (int i = 0; i < argc; i++)
	{
		arguments.push_back(argv[i]);
	}

	// Look for input type
	std::vector<std::string>::iterator position = std::find(arguments.begin(), arguments.end(), "-input");
	if (position != arguments.end())
	{
		int index = std::distance(arguments.begin(), position);

		// Check that there are enough input parameters. There should follow at least 2,
		// the type, e.g. "-f" for file, and then for example a filepath
		if (index + 2 >= arguments.size())
		{
			std::cout << "Not enough input parameters specified!" << std::endl;
			PrintHelp(GetProgramName(arguments[0]));
			return false;
		}
		else
		{
			// Start parsing input parameters
			// First parameter should always be the input type, followed by e.g. a path
			if (arguments[index + 1] == "-f")
			{
				inputType = InputType::FILE;
				inputFile = arguments[index + 2];
			}
		}
	}
	else
	{
		std::cout << "No input type specified!" << std::endl;
		PrintHelp(GetProgramName(arguments[0]));
		return false;
	}

	return true;
}