#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <vector>

Game::Game()
{
	m_window.create(sf::VideoMode(800, 600), "Reborn", sf::Style::Titlebar | sf::Style::Close);
	m_window.setFramerateLimit(60);
	
	obstSpawnTimerMax = 50.f ;
	obstSpawnTimer = obstSpawnTimerMax;
	colSpawnTimerMax = 30.f;
	colSpawnTimer = colSpawnTimerMax;
	isPause = false;
	
	player = new Player(m_window.getSize().x /2, m_window.getSize().y - 100 , 20);
}

Game::~Game()
{
	delete player;
	for (auto& e : obstacles)
	{
		delete e;
	}
	obstacles.clear();
	for (auto& e : collectibles)
	{
		delete e;
	}
	collectibles.clear();
}

const bool Game::IsRunning() const
{
	return m_window.isOpen();
}


void Game::SpawnObstacles()
{
	Obstacle* obst = new Obstacle(static_cast<float>(rand() % static_cast<int>(m_window.getSize().x - 70.f)), 0.f);
	obstacles.push_back(obst);
}

void Game::SpawnCollectibles()
{
	float x = static_cast<float>(rand() % static_cast<int>(m_window.getSize().x - 20.f));
	float y = 0.0f;
	int NbrCollect = (rand() % 10);
	for (int i = 0; i < NbrCollect; i++)
	{
		Collectible* col = new Collectible(x, y + (i*50.f));
		collectibles.push_back(col);
	}
}

void Game::UpdateObstacles()
{
	if (obstSpawnTimer >= obstSpawnTimerMax)
	{
		SpawnObstacles();
		SpawnObstacles();
		obstSpawnTimer = 0.f;
	}
	else
		obstSpawnTimer += 1.f;

	for (auto& e : obstacles)
	{
		e->Move();
	}
}

void Game::UpdateCollectibles()
{
	if (colSpawnTimer >= colSpawnTimerMax)
	{
		SpawnCollectibles();
		colSpawnTimer = 0.f;
	}
	else
		colSpawnTimer += 1.f;

	for (auto& e : collectibles)
	{
		e->Move();
	}
}

void Game::EventHandler()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				m_window.close();
			else if ((event.key.code == sf::Keyboard::Space) && (isPause))
				isPause = false;
			break;
		}

	}
}

void Game::Update()
{
	
	EventHandler();

	if (isPause)
		return;

	UpdateObstacles();
	UpdateCollectibles();

	player->Move(5.0);
	
	
	//collision
	for (auto& e : obstacles)
	{
		if(e->IsCollidingPlayer(player))
		{
			std::cout << "GAME OVER !!!!" << std::endl;
			isPause = true;

		}
	}
}

void Game::Render()
{
	m_window.clear();
	for (auto& e : obstacles)
	{
		e->Draw(m_window);
	}
	for (auto& e : collectibles)
	{
		e->Draw(m_window);
	}
	player->Draw(m_window);
	m_window.display();
}

