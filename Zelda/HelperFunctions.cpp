#include "pch.h"
#include "HelperFunctions.h"

void HelperFunctions::charactersCase(char* input)
{
	for (int i = 0; input[i] != '\0'; ++i)
	{
		if (input[i] >= 'a' && input[i] <= 'z')
		{
			input[i] = input[i] - 32;
		}
	}
}



void HelperFunctions::color(int k)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}