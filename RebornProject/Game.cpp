#include "stdafx.h"
#include "Game.h"
#include <iostream>

Game::Game()
{
	m_window.create(sf::VideoMode(800, 600), "Reborn", sf::Style::Titlebar | sf::Style::Close);
	m_window.setFramerateLimit(60);

	 player = new Player(390, 550, 20, sf::Color::Blue);

	 obst = new Obstacle(200, 200, sf::Vector2f(50, 50), (sf::Color::Red));
}

Game::~Game()
{
	m_window.close();
}

const bool Game::IsRunning() const
{
	return m_window.isOpen();
}

void Game::Update()
{
	while (m_window.pollEvent(m_ev))
	{
		switch (m_ev.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			if (m_ev.key.code == sf::Keyboard::Escape)
				m_window.close();
			break;
		}

	}

	player->Move(2.0);

	//collision
	if (player->getShape().getGlobalBounds().intersects(obst->getShape().getGlobalBounds()))
	{
		std::cout << "GAME OVER !!!!" << std::endl;
	}
}

void Game::Render()
{
	m_window.clear();
	player->draw(m_window);
	obst->draw(m_window);
	m_window.display();
}

