#include "pch.h"
#include "Game.h"
#include <windows.h>

int main()
{
	Game* zelda = new Game;
	zelda->Play();
	delete zelda;

	system("PAUSE");
	return 0;
}