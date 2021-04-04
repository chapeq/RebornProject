#include <iostream>
#include <stdafx.h>
#include "Game.h"

int main()
{
	Game game{};
	srand((unsigned)time(NULL));

	game.RunGameLoop();

	return EXIT_SUCCESS;
}


