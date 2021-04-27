#include "stdafx.h"
#include "Game.h"
#include <iostream>

static const float PLAYER_MAX_SIZE{ 80.0f };

Game::Game() : GameEngine{}
{
	GetInitConfig(initConfig);
	currentConfig = initConfig;
	tempConfig = initConfig;

	game.player = new Player(initConfig.playerSpeed, initConfig.playerRadius);
	game.player->SetPosition(sf::Vector2f(m_windowSize.x / 2, m_windowSize.y - 50));
	m_Timer->SetCollectibleSpawnTime(initConfig.collectibleSpawnTime);
	m_Timer->SetObstacleSpawnTime(initConfig.obstacleSpawnTime);
}

Game::~Game()
{
	delete game.player;
	for (auto& c : game.collectibles)
	{
		delete c;
	}
	for (auto& o : game.obstacles)
	{
		delete o;
	}
}


void Game::SpawnObstacles()
{
	Obstacle* obst = new Obstacle(currentConfig.obstacleSpeed);
	float x = static_cast<float>(rand() % static_cast<int>(m_windowSize.x - obst->GetSize().x) + (obst->GetSize().x / 2));
	float y = -20.0f; //offset
	obst->SetPosition(sf::Vector2f(x, y));
	game.obstacles.push_back(obst);
}


void Game::CheckObstacleSpawn()
{
	// Respawn if collide with other obstacle
	if (game.obstacles.size() < 2)
	{
		return;
	}

	int current = game.obstacles.size() - 1;
	int cptAttempt = 0;

	while (current > 0 && cptAttempt < 10)
	{
		int previous = current - 1;
		if (game.obstacles[current]->GetBounds().intersects(game.obstacles[previous]->GetBounds()))
		{
			delete game.obstacles[current];
			game.obstacles.erase(game.obstacles.begin() + current);
			SpawnObstacles();
			cptAttempt++;
		}
		else
			current--;
	}

}

void Game::UpdateObstacles()
{
	//Spawn
	int randNbrObst = rand() % currentConfig.nbrMaxObstacle + 1;

	if (m_Timer->TriggerObstacleSpawn())
	{
		for (int i = 0; i < randNbrObst; i++)
		{
			SpawnObstacles();
		}
		CheckObstacleSpawn();
	}

	//Update
	for (int i = 0; i < game.obstacles.size(); i++)
	{
		//Move Down
		game.obstacles[i]->Move(m_Timer->GetDeltaTime());

		//Check collision with player
		if (game.obstacles[i]->GetBounds().intersects(game.player->GetBounds()))
		{
			LoseAndReborn();
		}
	}

	for (int i = game.obstacles.size() - 1; i >= 0; i--)
	{
		if (game.obstacles[i]->GetPosition().y > m_windowSize.y)
		{
			delete game.obstacles[i];
			game.obstacles.erase(game.obstacles.begin() + i);
		}
	}
}

void Game::SpawnCollectibles()
{
	int randNbrCol = rand() % currentConfig.nbrMaxCollectible + 1;
	Collectible* firstCol = new Collectible(currentConfig.collectibleSpeed);
	float x = static_cast<float>(rand() % static_cast<int>(m_windowSize.x - (firstCol->GetRadius() * 2)) + (firstCol->GetRadius()));
	float y = -20.0f; //offset
	firstCol->SetPosition(sf::Vector2f(x, y));
	game.collectibles.push_back(firstCol);

	//Spawn next collectibles with 10.f offset between each other on y axis
	for (int i = 1; i < randNbrCol + 1; i++)
	{
		Collectible* nextCol = new Collectible(currentConfig.collectibleSpeed);
		nextCol->SetPosition(sf::Vector2f(x, i * ((nextCol->GetRadius() * 2) + 10.0f)));
		game.collectibles.push_back(nextCol);
	}

}

void Game::CheckCollectibleSpawn()
{
	//Erase if collide with obstacle
	for (auto& e : game.obstacles)
	{
		for (int i = game.collectibles.size() - 1; i >= 0; i--)
		{
			if (game.collectibles[i]->GetBounds().intersects(e->GetBounds()))
			{
				delete game.collectibles[i];
				game.collectibles.erase(game.collectibles.begin() + i);
			}
		}
	}
}

void Game::UpdateCollectibles()
{
	//Spawn
	if (m_Timer->TriggerCollectibleSpawn())
	{
		SpawnCollectibles();
	}

	CheckCollectibleSpawn();

	//Update
	for (int i = 0; i < game.collectibles.size(); i++)
	{
		//Move Down
		game.collectibles[i]->Move(m_Timer->GetDeltaTime());
	}

	for (int i = game.collectibles.size() - 1; i >= 0; i--)
	{
		//Check collision with player
		if (game.collectibles[i]->GetBounds().intersects(game.player->GetBounds()))
		{
			delete game.collectibles[i];
			game.collectibles.erase(game.collectibles.begin() + i);
			game.player->AddPoints(1);
			std::string score = "Score : " + std::to_string(game.player->GetScore());
			m_manager.Scoring(score);
		}
		//Erase if out of bounds
		else if (game.collectibles[i]->GetPosition().y > m_windowSize.y)
		{
			delete game.collectibles[i];
			game.collectibles.erase(game.collectibles.begin() + i);
		}
	}
}

bool Game::CheckIfGameOver()
{
	if (game.player->GetRadius() >= PLAYER_MAX_SIZE)
	{
		m_State = GameState::End;
		m_manager.GameOver();
		game.obstacles.clear();
		game.collectibles.clear();
		return true;
	}
	else
		return false;
}

void Game::LoseAndReborn()
{
	if (!CheckIfGameOver())
	{
		m_State = GameState::Lose;
		m_manager.Losing();

		for (auto& c : game.collectibles)
		{
			delete c;
		}
		for (auto& o : game.obstacles)
		{
			delete o;
		}
		game.obstacles.clear();
		game.collectibles.clear();

		float newRadius = game.player->GetRadius() + 5;
		game.player->SetRadius(newRadius);
		game.player->SetOrigin(newRadius, newRadius);
		game.player->SetPosition(sf::Vector2f(m_windowSize.x / 2, m_windowSize.y - 50));

	}
}

void Game::Update()
{
	if (m_State != GameState::Playing)
		return;

	UpdateObstacles();
	UpdateCollectibles();

	/*AI function - development in progress*/
	//player->MoveToCollect(collectibles, obstacles, m_windowSize, m_Timer->GetDeltaTime());

	game.player->Move(m_Timer->GetDeltaTime());
	game.player->CheckWindowBounds(m_windowSize);

	if (m_Timer->TriggerLevelUp() && currentConfig.increaseDifficulty)
	{
		currentConfig.collectibleSpeed += 30.0f;
		currentConfig.obstacleSpeed += 30.0f;
		m_Timer->SetCollectibleSpawnTime(m_Timer->GetCollectibleSpawnTime() - 0.05f);
		m_Timer->SetObstacleSpawnTime(m_Timer->GetObstacleSpawnTime() - 0.05f);
		game.player->SetSpeed(game.player->GetSpeed() + 30.0f);
	}

}

void Game::Render(sf::RenderTarget& target)
{
	target.clear();
	m_manager.DrawUI(target);
	for (auto& c : game.collectibles)
	{
		c->Draw(target);
	}
	for (auto& o : game.obstacles)
	{
		o->Draw(target);
	}
	//player->DrawBounds(target); // debug colliders for AI part
	game.player->Draw(target);
}



void Game::RenderDebugMenu(sf::RenderTarget& target)
{
	ImGui::Begin("Configuration window");
	ImGui::NewLine();

	ImGui::Checkbox("Increase difficulty over time", &tempConfig.increaseDifficulty);

	ImGui::NewLine();
	if (ImGui::CollapsingHeader("Obstacles and Collectibles : "))
	{
		ImGui::SliderFloat("CollectibleSpeed", &tempConfig.collectibleSpeed, 100.0f, 900.0f, "%.1f");
		ImGui::SliderFloat("ObstacleSpeed", &tempConfig.obstacleSpeed, 100.0f, 900.0f, "%.1f");
		ImGui::SliderFloat("CollectibleSpawnTime", &tempConfig.collectibleSpawnTime, 0.2f, 5.0f, "%.2f");
		ImGui::SliderFloat("ObstacleSpawnTime", &tempConfig.obstacleSpawnTime, 0.2f, 5.0f, "%.2f");
		ImGui::SliderInt("NbrMaxCollectible", &tempConfig.nbrMaxCollectible, 1, 15);
		ImGui::SliderInt("NbrMaxObstacle", &tempConfig.nbrMaxObstacle, 1, 10);
	}

	if (ImGui::CollapsingHeader("Player : "))
	{
		ImGui::SliderFloat("Speed", &tempConfig.playerSpeed, 100.0f, 900.0f, "%.1f");
		ImGui::SliderFloat("Size", &tempConfig.playerRadius, 10.0f, 200.0f, "%.1f");
	}

	ImGui::NewLine();

	if (ImGui::Button("Apply parameters"))
	{
		currentConfig = tempConfig;

		m_Timer->SetCollectibleSpawnTime(currentConfig.collectibleSpawnTime);
		m_Timer->SetObstacleSpawnTime(currentConfig.obstacleSpawnTime);
		game.player->SetSpeed(currentConfig.playerSpeed);
		game.player->SetRadius(currentConfig.playerRadius);
	}
	ImGui::SameLine();
	if (ImGui::Button("Reset initial parameters "))
	{
		currentConfig = initConfig;
		tempConfig = initConfig;

		m_Timer->SetCollectibleSpawnTime(currentConfig.collectibleSpawnTime);
		m_Timer->SetObstacleSpawnTime(currentConfig.obstacleSpawnTime);
		game.player->SetSpeed(currentConfig.playerSpeed);
		game.player->SetRadius(currentConfig.playerRadius);
	}
	ImGui::SameLine();
	if (ImGui::Button("Get current parameters"))
	{
		if (!game.obstacles.empty())
			currentConfig.obstacleSpeed = game.obstacles.back()->GetSpeed();
		if (!game.collectibles.empty())
			currentConfig.collectibleSpeed = game.collectibles.back()->GetSpeed();

		currentConfig.obstacleSpawnTime = m_Timer->GetObstacleSpawnTime();
		currentConfig.collectibleSpawnTime = m_Timer->GetCollectibleSpawnTime();
		currentConfig.playerRadius = game.player->GetRadius();
		currentConfig.playerSpeed = game.player->GetSpeed();

		tempConfig = currentConfig;
	}

	ImGui::End();
}

