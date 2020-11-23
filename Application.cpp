#include <iostream>

#include "CharacterCount.h"

int main()
{
	g_CharCount = new CharacterCount();

	const char* text = "aaaabbbcccccc122333ABBCCC";
	g_CharCount->CountChars(reinterpret_cast<const unsigned char*>(text));

	std::cout << g_CharCount->PrintToStream().str() << std::endl;

	delete g_CharCount;

	int ret = std::getchar();

	return 0;
}