#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <vector>

static const float OBSTACLE_TIMER{ 50.0f };
static const float COLLECTIBLE_TIMER{ 50.0f };
static const int NBR_MAX_OBSTACLE{ 3 };
static const int NBR_MAX_COLLECTIBLE{ 6 };
static const float SPEED_ITEMS{ 7.0f };
static const float SPEED_PLAYER{ 5.0f };


Game::Game()
{
	m_window.create(sf::VideoMode(800, 600), "Reborn", sf::Style::Titlebar | sf::Style::Close);
	m_window.setFramerateLimit(60);
	
	obstacleSpawnTimerMax = OBSTACLE_TIMER;
	obstacleSpawnTimer = obstacleSpawnTimerMax;
	collectibleSpawnTimerMax = COLLECTIBLE_TIMER;
	collectibleSpawnTimer = collectibleSpawnTimerMax;
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
	float x = static_cast<float>(rand() % static_cast<int>(m_window.getSize().x));
	float y = 0.0f;
	Obstacle* obst = new Obstacle(x,y);
	obstacles.push_back(obst);
}

void Game::SpawnCollectibles()
{
	int  randNbrCol = rand() % NBR_MAX_COLLECTIBLE;
	float x = static_cast<float>(rand() % static_cast<int>(m_window.getSize().x));
	for (int i = 0; i < randNbrCol; i++)
	{
		Collectible* col = new Collectible(x, i * 50.0f);
		collectibles.push_back(col);
	}
			
}

void Game::UpdateObstacles()
{
	int randNbrObst = rand() % NBR_MAX_OBSTACLE + 1;

	if (obstacleSpawnTimer >= obstacleSpawnTimerMax)
	{
		for (int i = 0; i < randNbrObst; i++)
		{
			SpawnObstacles();
		}
		obstacleSpawnTimer = 0.f;
	}
	else
		obstacleSpawnTimer += 1.f;

	for (auto& e : obstacles)
	{
		e->Move(SPEED_ITEMS);
	}
}


void Game::UpdateCollectibles()
{
	
	if (collectibleSpawnTimer >= collectibleSpawnTimerMax)
	{
		SpawnCollectibles();
		collectibleSpawnTimer = 0.f;
	}
	else
		collectibleSpawnTimer += 1.f;

	for (auto& e : collectibles)
	{
		e->Move(SPEED_ITEMS);
	}
}

void Game::Restart()
{
	std::cout << "GAME OVER !!!!" << std::endl;
	std::cout << "Hit Space to Restart" << std::endl;
	isPause = true;

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

	player->SetRadius(player->GetRadius() + 5);
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

	player->Move(SPEED_PLAYER);
	
	
	//collision
	for (auto& e : obstacles)
	{
		if(e->getBounds().intersects(player->getBounds()))
		{
			Restart();
		}
	}
	for (int i=0 ; i < collectibles.size(); i++)
	{
		if (collectibles[i]->getBounds().intersects(player->getBounds()))
		{
			collectibles.erase(collectibles.begin() + i);
			player->AddPoints(1);
			std::cout << "Score :" << player->GetScore() << std::endl;
		}
	}
}

void Game::Render()
{
	m_window.clear();

	for (auto& c : collectibles)
	{
		c->Draw(m_window);
	}
	for (auto& o : obstacles)
	{
		o->Draw(m_window);
	}
	player->Draw(m_window);
	m_window.display();
}

