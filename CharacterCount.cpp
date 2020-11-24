#include <iostream>

#include "CharacterCount.h"

CharacterCount* g_CharCount = nullptr;
int* asmCountMap = nullptr;


bool CharacterCount::CountChars(const unsigned char* buffer)
{
	for (int i = 0; buffer[i]; i++)
	{
		this->countMap[buffer[i]]++;
	}

	return true;
}

std::ostringstream CharacterCount::PrintToStream(int* countMap)
{
	std::ostringstream stream;

	for (unsigned char c : encodingTable)
	{
		stream << c << ": " << countMap[c] << "x" << std::endl;
	}

	return stream;
}

__declspec(naked) void AsmCountChars(const unsigned char* buffer)
{
	__asm
	{
		loopstart: mov dl, byte ptr[buffer]          // dl=data[0] 
		inc dword ptr[asmCountMap + edx * 4]    // quantity[char]++
		inc buffer
		cmp  byte ptr[buffer], 0
		jne loopstart
	}
}
