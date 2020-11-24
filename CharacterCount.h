#pragma once

#ifndef CHAR_COUNT

#define CHAR_COUNT
#include <sstream>
#include <vector>

class CharacterCount
{
public:
	int countMap[256];
public:
	// Scans the given (null-terminated) buffer string and updates the countMap
	bool CountChars(const unsigned char* buffer);
	std::ostringstream PrintToStream(int* countMap);
};

static std::vector<unsigned char> encodingTable = {
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
			'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
			'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
			'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
			'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
			'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
			'w', 'x', 'y', 'z', '0', '1', '2', '3',
			'4', '5', '6', '7', '8', '9' };

// Assembly stuff
void AsmCountChars(const unsigned char* buffer);
extern int* asmCountMap;

extern CharacterCount* g_CharCount;

#endif // CHAR_COUNT