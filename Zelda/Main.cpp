#include "pch.h"
#include "./test.cpp"
#include <windows.h>
int main()
{
	Game game = new Game();
	game->Play();

	system("PAUSE");
	return 0;
}
