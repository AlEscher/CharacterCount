#pragma once
#include <string>

enum class InputType
{
	FILE = 0,
	URL,
	CLIPBOARD,
};

std::string GetProgramName(std::string pathToProgram);
void PrintHelp(std::string pathToProgram);
bool ParseCommandLineArgs(int argc, char* argv[], std::string& inputFile, InputType& inputType);