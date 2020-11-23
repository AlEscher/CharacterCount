#include <iostream>

#include "CharacterCount.h"

CharacterCount* g_CharCount = nullptr;


bool CharacterCount::CountChars(const unsigned char* buffer)
{
	for (int i = 0; buffer[i]; i++)
	{
		this->countMap[buffer[i]]++;
	}

	return true;
}

std::ostringstream CharacterCount::PrintToStream()
{
	std::ostringstream stream;

	for (unsigned char c : encodingTable)
	{
		stream << c << ": " << this->countMap[c] << "x" << std::endl;
	}

	return stream;
}
