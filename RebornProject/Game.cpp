#include "stdafx.h"
#include "Game.h"
#include <iostream>

static const float PLAYER_MAX_SIZE{ 80.0f };

Game::Game() : GameEngine{}
{
	GetInitConfig(initConfig);
	currentConfig = initConfig;
	tempConfig = initConfig;

	currentState.player = new Player(initConfig.playerSpeed, initConfig.playerRadius);
	currentState.player->SetPosition(sf::Vector2f(m_windowSize.x / 2, m_windowSize.y - 50));
	m_Timer->SetCollectibleSpawnTime(initConfig.collectibleSpawnTime);
	m_Timer->SetObstacleSpawnTime(initConfig.obstacleSpawnTime);
}

Game::~Game()
{
	delete currentState.player;
	for (auto& collectible : currentState.collectibles)
	{
		delete collectible;
	}
	for (auto& obstacle : currentState.obstacles)
	{
		delete obstacle;
	}
}


void Game::SpawnObstacles()
{
	Obstacle* obstacle = new Obstacle(currentConfig.obstacleSpeed);
	float x = static_cast<float>(rand() % static_cast<int>(m_windowSize.x - obstacle->GetSize().x) + (obstacle->GetSize().x / 2));
	float y = -20.0f; //offset
	obstacle->SetPosition(sf::Vector2f(x, y));
	currentState.obstacles.push_back(obstacle);
}


void Game::CheckObstacleSpawn()
{
	// Respawn if collide with other obstacle
	if (currentState.obstacles.size() < 2)
	{
		return;
	}

	int current = currentState.obstacles.size() - 1;
	int cptAttempt = 0;

	while (current > 0 && cptAttempt < 10)
	{
		int previous = current - 1;
		if (currentState.obstacles[current]->GetBounds().intersects(currentState.obstacles[previous]->GetBounds()))
		{
			delete currentState.obstacles[current];
			currentState.obstacles.erase(currentState.obstacles.begin() + current);
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
	for (int i = 0; i < currentState.obstacles.size(); i++)
	{
		//Move Down
		currentState.obstacles[i]->Move(m_Timer->GetDeltaTime());

		//Check collision with player
		if (currentState.obstacles[i]->GetBounds().intersects(currentState.player->GetBounds()))
		{
			LoseAndReborn();
		}
	}

	for (int i = currentState.obstacles.size() - 1; i >= 0; i--)
	{
		if (currentState.obstacles[i]->GetPosition().y > m_windowSize.y)
		{
			delete currentState.obstacles[i];
			currentState.obstacles.erase(currentState.obstacles.begin() + i);
		}
	}
}

void Game::SpawnCollectibles()
{
	int randNbrCol = rand() % currentConfig.nbrMaxCollectible + 1;
	Collectible* FirstColl = new Collectible(currentConfig.collectibleSpeed);
	float x = static_cast<float>(rand() % static_cast<int>(m_windowSize.x - (FirstColl->GetRadius() * 2)) + (FirstColl->GetRadius()));
	float y = -20.0f; //offset
	FirstColl->SetPosition(sf::Vector2f(x, y));
	currentState.collectibles.push_back(FirstColl);

	//Spawn next collectibles with 10.f offset between each other on y axis
	for (int i = 1; i < randNbrCol + 1; i++)
	{
		Collectible* nextColl = new Collectible(currentConfig.collectibleSpeed);
		nextColl->SetPosition(sf::Vector2f(x, i * ((nextColl->GetRadius() * 2) + 10.0f)));
		currentState.collectibles.push_back(nextColl);
	}

}

void Game::CheckCollectibleSpawn()
{
	//Erase if collide with obstacle
	for (auto& obstacle : currentState.obstacles)
	{
		for (int i = currentState.collectibles.size() - 1; i >= 0; i--)
		{
			if (currentState.collectibles[i]->GetBounds().intersects(obstacle->GetBounds()))
			{
				delete currentState.collectibles[i];
				currentState.collectibles.erase(currentState.collectibles.begin() + i);
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
	for (int i = 0; i < currentState.collectibles.size(); i++)
	{
		//Move Down
		currentState.collectibles[i]->Move(m_Timer->GetDeltaTime());
	}

	for (int i = currentState.collectibles.size() - 1; i >= 0; i--)
	{
		//Check collision with player
		if (currentState.collectibles[i]->GetBounds().intersects(currentState.player->GetBounds()))
		{
			delete currentState.collectibles[i];
			currentState.collectibles.erase(currentState.collectibles.begin() + i);
			currentState.player->AddPoints(1);
			std::string score = "Score : " + std::to_string(currentState.player->GetScore());
			m_manager.Scoring(score);
		}
		//Erase if out of bounds
		else if (currentState.collectibles[i]->GetPosition().y > m_windowSize.y)
		{
			delete currentState.collectibles[i];
			currentState.collectibles.erase(currentState.collectibles.begin() + i);
		}
	}
}

bool Game::CheckIfGameOver()
{
	if (currentState.player->GetRadius() >= PLAYER_MAX_SIZE)
	{
		m_State = GameState::End;
		m_manager.GameOver();
		currentState.obstacles.clear();
		currentState.collectibles.clear();
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

		for (auto& collectible : currentState.collectibles)
		{
			delete collectible;
		}
		for (auto& obstacle : currentState.obstacles)
		{
			delete obstacle;
		}
		currentState.obstacles.clear();
		currentState.collectibles.clear();

		float newRadius = currentState.player->GetRadius() + 5;
		currentState.player->SetRadius(newRadius);
		currentState.player->SetOrigin(newRadius, newRadius);
		currentState.player->SetPosition(sf::Vector2f(m_windowSize.x / 2, m_windowSize.y - 50));

	}
}


void Game::Update()
{
	if (m_State != GameState::Playing)
		return;

	UpdateObstacles();
	UpdateCollectibles();

	if (currentConfig.AIOn)
	{
		aiPlayer.MoveAI(currentState, m_windowSize, m_Timer->GetDeltaTime());
	}
	else
	{
		currentState.player->Move(m_Timer->GetDeltaTime());
	}
	
	currentState.player->CheckWindowBounds(m_windowSize);

	if (m_Timer->TriggerLevelUp() && currentConfig.increaseDifficulty)
	{
		currentConfig.collectibleSpeed += 30.0f;
		currentConfig.obstacleSpeed += 30.0f;
		m_Timer->SetCollectibleSpawnTime(m_Timer->GetCollectibleSpawnTime() - 0.05f);
		m_Timer->SetObstacleSpawnTime(m_Timer->GetObstacleSpawnTime() - 0.05f);
		currentState.player->SetSpeed(currentState.player->GetSpeed() + 30.0f);
	}

}

void Game::Render(sf::RenderTarget& target)
{
	target.clear();
	m_manager.DrawUI(target);
	for (auto& collectible : currentState.collectibles)
	{
		collectible->Draw(target);
	}
	for (auto& obstacle : currentState.obstacles)
	{
		obstacle->Draw(target);
	}
	//currentState.player->DrawBounds(target); // debug colliders for AI part
	currentState.player->Draw(target);
}



void Game::RenderDebugMenu(sf::RenderTarget& target)
{
	
	ImGui::Begin("Configuration window");
	ImGui::NewLine();
	ImGui::Checkbox("Activate AI", &tempConfig.AIOn);

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
		currentState.player->SetSpeed(currentConfig.playerSpeed);
		currentState.player->SetRadius(currentConfig.playerRadius);
	}
	ImGui::SameLine();
	if (ImGui::Button("Reset initial parameters "))
	{
		currentConfig = initConfig;
		tempConfig = initConfig;

		m_Timer->SetCollectibleSpawnTime(currentConfig.collectibleSpawnTime);
		m_Timer->SetObstacleSpawnTime(currentConfig.obstacleSpawnTime);
		currentState.player->SetSpeed(currentConfig.playerSpeed);
		currentState.player->SetRadius(currentConfig.playerRadius);
	}
	ImGui::SameLine();
	if (ImGui::Button("Get current parameters"))
	{
		if (!currentState.obstacles.empty())
			currentConfig.obstacleSpeed = currentState.obstacles.back()->GetSpeed();
		if (!currentState.collectibles.empty())
			currentConfig.collectibleSpeed = currentState.collectibles.back()->GetSpeed();

		currentConfig.obstacleSpawnTime = m_Timer->GetObstacleSpawnTime();
		currentConfig.collectibleSpawnTime = m_Timer->GetCollectibleSpawnTime();
		currentConfig.playerRadius = currentState.player->GetRadius();
		currentConfig.playerSpeed = currentState.player->GetSpeed();

		tempConfig = currentConfig;
	}

	ImGui::End();
}

