#include <iostream>

#include "CharacterCount.h"

int main()
{
	g_CharCount = new CharacterCount();

	const char* text = "aaaabbbcccccc122333ABBCCC";
	g_CharCount->CountChars(reinterpret_cast<const unsigned char*>(text));
	AsmCountChars(reinterpret_cast<const unsigned char*>(text));

	std::cout << g_CharCount->PrintToStream(g_CharCount->countMap).str() << std::endl;

	std::cout << g_CharCount->PrintToStream(asmCountMap).str() << std::endl;

	delete g_CharCount;

	int ret = std::getchar();

	return 0;
}