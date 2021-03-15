#include <iostream>
#include <stdafx.h>
#include "Game.h"

int main()
{
	Game game{};
	srand((unsigned)time(NULL));

	std::cout << "HELLO" << std::endl;

	game.RunGameLoop();


	return EXIT_SUCCESS;
}

