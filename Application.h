#pragma once
#include <string>

enum class InputType
{
	FILE = 0,
	URL,
	CLIPBOARD,
};

enum class OutputType
{
	FILE = 0,
	CONSOLE,
};

// Get the program name from its path
std::string GetProgramName(const std::string& pathToProgram);
// Prints a help text explaining the usage of this program
void PrintHelp(const std::string& pathToProgram);
// Parse arguments. Returns false if any crucial arguments are missing
bool ParseCommandLineArgs(int argc, char* argv[], std::string& inputFile, InputType& inputType, std::string& outputParam, OutputType& outputType);