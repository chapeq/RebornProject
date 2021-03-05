#include <stdafx.h>
#include <Game.h>
#include <iostream>



int main()
{
	
	Game game;

	std::cout << "HELLO" << std::endl;

	
	while (game.IsRunning())
	{ 
		game.Update();
		game.Render();
				
	}
}
