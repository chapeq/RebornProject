#include <stdafx.h>
#include <Game.h>
#include <iostream>



int main()
{
	
	Game game;
	srand((unsigned)time(NULL));

	std::cout << "HELLO" << std::endl;

	
	while (game.IsRunning())
	{ 
		game.Update();
		game.Render();
				
	}
}
