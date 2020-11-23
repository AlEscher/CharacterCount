#include <iostream>

#include "CharacterCount.h"

void PrintHelp(std::string param)
{
	std::string programName = "";
	std::vector<std::string> elements;
	std::istringstream f(param);
	// Get program name from command line argument containing program path
	while (getline(f, programName, '\\'))
	{
	}

	std::cout << "CharCounter usage:" << std::endl;
	std::cout << "\t* -input  : The following arguments specify the input type" << std::endl;
	std::cout << "\t* -f	  : The following argument specifies the path to an input file" << std::endl;
	std::cout << "\t* -output : The following argument specifies the output type" << std::endl;
	std::cout << "\t*" << std::endl;
	std::cout << "\t* Example: " << std::endl;
	std::cout << "\t- Reads the text from Input.txt and writes the result to Output.txt (creating the output file if it doesn't exist):" << std::endl;
	std::cout << "\t- .\\" << programName << " -input -f C:/Path/To/Input.txt -output -f C:/Path/To/Output.txt" <<  std::endl;

	int ret = std::getchar();
}

int main(int argc, char* argv[], char* envp[])
{
	if (argc == 1)
	{
		PrintHelp(argv[0]);
		return -1;
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