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

	isPause = true;
	
	player = new Player();
	player->SetPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y - 50));

	if (!fontStart.loadFromFile("Assets/retro.ttf"))
		std::cout << "ERROR Failed to load font" << std::endl;

	startText.setFont(this->fontStart);
	startText.setCharacterSize(80);
	startText.setFillColor(sf::Color::White);
	startText.setPosition(100, 200);
	startText.setString("Press Space To Start !");

	if (!fontScore.loadFromFile("Assets/rainyhearts.ttf"))
		std::cout << "ERROR Failed to load font" << std::endl;

	scoreText.setFont(this->fontScore);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(0, 0);
	scoreText.setString("Score : 0");
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
	Obstacle* obst = new Obstacle();
	float x = static_cast<float>(rand() % static_cast<int>(m_window.getSize().x - obst->getSize().x));
	float y = -10.0f;
	obst->SetPosition(x, y);
	obstacles.push_back(obst);
}

void Game::SpawnCollectibles()
{
	int  randNbrCol = rand() % NBR_MAX_COLLECTIBLE + 2;
	Collectible* firstcol = new Collectible();
	float x = static_cast<float>(rand() % static_cast<int>(m_window.getSize().x - (firstcol->GetRadius()*2)));
	float y = -10.0f;
	firstcol->SetPosition(x, y);
	collectibles.push_back(firstcol);

	for (int i = 1; i < randNbrCol+1 ; i++)
	{
		Collectible* nextcol = new Collectible();
		nextcol->SetPosition(x , i * ((nextcol->GetRadius()*2) + 10.0f));
		collectibles.push_back(nextcol);
	}
			
}

void Game::UpdateObstacles()
{
	//Spawn
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

	//Update
	int cpt = 0;
	for (auto& e : obstacles)
	{
		//Move Down
		e->Move(SPEED_ITEMS);

		// check player collision
		if (e->getBounds().intersects(player->getBounds()))
		{
			Restart();
		}

		//Delete if out of bounds
		if (e->GetPosition().y > m_window.getSize().y)
		{
			delete obstacles.at(cpt);
			obstacles.erase(obstacles.begin() + cpt);
		}

		cpt++;
	}
}


void Game::UpdateCollectibles()
{
	//Spawn
	if (collectibleSpawnTimer >= collectibleSpawnTimerMax)
	{
		SpawnCollectibles();
		collectibleSpawnTimer = 0.f;
	}
	else
		collectibleSpawnTimer += 1.f;
	
	//Update
	for (auto& e : obstacles)
	{
		//Delete if overlap by obstacle
		for (int i = 0; i < collectibles.size(); i++)
		{
			if (collectibles[i]->getBounds().intersects(e->getBounds()))
			{
				delete collectibles.at(i);
				collectibles.erase(collectibles.begin() + i);
			}
		}
	}
	
	for (int i = 0; i < collectibles.size(); i++)
	{

		//Move Down
		collectibles[i]->Move(SPEED_ITEMS);

		//Check collision with player
		if (collectibles[i]->getBounds().intersects(player->getBounds()))
		{
			delete collectibles.at(i);
			collectibles.erase(collectibles.begin() + i);
			player->AddPoints(1);
			std::string score = "Score : " + std::to_string(player->GetScore());
			scoreText.setString(score);
		}
	}

	for (int i = 0; i < collectibles.size(); i++)
	{
		//Delete if out of bounds
		if (collectibles[i]->GetPosition().y > m_window.getSize().y)
		{
			delete collectibles.at(i);
			collectibles.erase(collectibles.begin() + i);
		}

	}
}

void Game::Restart()
{
	startText.setString("You Died ! Press R To Reborn !");
	startText.setPosition(70, 200);
	startText.setCharacterSize(70);
	startText.setFillColor(sf::Color::White);
	isPause = true;

	for (auto& e : obstacles)
	{
		delete e;
	}
	obstacles.clear();
	for (auto& f : collectibles)
	{
		delete f;
	}
	collectibles.clear();
	
	float newRadius = player->GetRadius() + 5;
	player->SetRadius(newRadius);
	player->SetOrigin(newRadius, newRadius);
	player->SetPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y - 50));
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
			{
				isPause = false;
				startText.setCharacterSize(0);
				startText.setFillColor(sf::Color::Black);
			}
			else if ((event.key.code == sf::Keyboard::R) && (isPause))
			{
				isPause = false;
				startText.setCharacterSize(0);
				startText.setFillColor(sf::Color::Black);
			}
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
	
}

void Game::Render()
{
	m_window.clear();
	m_window.draw(startText);
	m_window.draw(scoreText);
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

