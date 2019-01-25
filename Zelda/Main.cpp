#include "pch.h"
#include <windows.h>
#include "Zelda.h"

int main()
{
	Game* zelda = new Game;
	zelda->Play();
	delete zelda;

	system("PAUSE");
	return 0;
}