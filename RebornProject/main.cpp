#include <stdafx.h>
#include <Player.h>
#include <Obstacle.h>
#include <string>
#include <iostream>

sf::RenderWindow window;

int main()
{
	//creation fenetre
	window.create(sf::VideoMode(800, 600), "Reborn");
	window.setFramerateLimit(60);

	//creation player
	Player cercle(390, 550, 20, sf::Color::Blue);

	//creation obstacle
	Obstacle rect(200, 200, sf::Vector2f(50, 50), (sf::Color::Red));


	std::cout << "HELLO" << std::endl;

	//affichage fenetre
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}

				break;
			}
			case sf::Event::Resized:
			{
				break;
			}
			}
		}

		//Deplacements clavier
		cercle.Move(2.0);

		//collision
		if(rect.IsColliding(cercle))
		{
			std::cout << "GAME OVER !!!!" << std::endl;
		}

		//dessine,affiche, met a jour
		window.draw(cercle);
		window.draw(rect);
		window.display();
		window.clear();
	}
}
