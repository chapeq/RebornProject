#include "stdafx.h"
#include "Game.h"
#include <iostream>

static const float PLAYER_MAX_SIZE{ 80.0f };

Game::Game() : GameEngine{}
{
	GetInitConfig(initConfig);
	currentConfig = initConfig;
	tempConfig = initConfig;
	
	player = new Player(initConfig.playerSpeed, initConfig.playerRadius);
	player->SetPosition(sf::Vector2f(m_windowSize.x / 2, m_windowSize.y - 50));	
	m_Timer->SetCollectibleSpawnTime(initConfig.collectibleSpawnTime);
	m_Timer->SetObstacleSpawnTime(initConfig.obstacleSpawnTime);

}

Game::~Game()
{
	delete player;
	for (auto& c : collectibles)
	{
		delete c;
	}
	for (auto& o : obstacles)
	{
		delete o;
	}
}


void Game::SpawnObstacles()
{
	Obstacle* obst = new Obstacle(currentConfig.obstacleSpeed) ;
	float x = static_cast<float>(rand() % static_cast<int>(m_windowSize.x - obst->GetSize().x));
	float y = -20.0f; //offset
	obst->SetPosition(sf::Vector2f(x, y));
	obstacles.push_back(obst);
}


void Game::CheckObstacleSpawn()
{
	//Respawn if collide with other obstacle
	int current = 1;
	int cptAttempt = 0;

	if (obstacles.size() >= 2)
	{
		while (current < obstacles.size() && cptAttempt < 10)
		{
			int previous = current - 1;
			if (obstacles[current]->GetBounds().intersects(obstacles[previous]->GetBounds()))
			{
				delete obstacles[current];
				obstacles.erase(obstacles.begin() + current);
				SpawnObstacles();
				cptAttempt++;
			}
			else
				current++;
		}
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
	for (int i = 0; i < obstacles.size(); i++)
	{
		//Move Down
		obstacles[i]->Move(m_Timer->GetDeltaTime());

		//Check collision with player
		if (obstacles[i]->GetBounds().intersects(player->GetBounds()))
		{
			LoseAndReborn();
		}
		//Erase if out of bounds
		else if (obstacles[i]->GetPosition().y > m_windowSize.y)
		{
			delete obstacles[i];
			obstacles.erase(obstacles.begin() + i);
		}
	}
}

void Game::SpawnCollectibles()
{
	int randNbrCol = rand() % currentConfig.nbrMaxCollectible + 1;
	Collectible* firstCol = new Collectible(currentConfig.collectibleSpeed);
	float x = static_cast<float>(rand() % static_cast<int>(m_windowSize.x - (firstCol->GetRadius() * 2)));
	float y = -20.0f; //offset
	firstCol->SetPosition(sf::Vector2f(x, y));
	collectibles.push_back(firstCol);

	//Spawn next collectibles with 10.f offset between each other on y axis
	for (int i = 1; i < randNbrCol + 1; i++)
	{
		Collectible* nextCol = new Collectible(currentConfig.collectibleSpeed);
		nextCol->SetPosition(sf::Vector2f(x, i * ((nextCol->GetRadius() * 2) + 10.0f)));
		collectibles.push_back(nextCol);
	}

}

void Game::CheckCollectibleSpawn()
{
	//Erase if collide with obstacle
	for (auto& e : obstacles)
	{
		for (int i = 0; i < collectibles.size(); i++)
		{
			if (collectibles[i]->GetBounds().intersects(e->GetBounds()))
			{
				delete collectibles[i];
				collectibles.erase(collectibles.begin() + i);
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
	for (int i = 0; i < collectibles.size(); i++)
	{
		//Move Down
		collectibles[i]->Move(m_Timer->GetDeltaTime());

		//Check collision with player
		if (collectibles[i]->GetBounds().intersects(player->GetBounds()))
		{
			m_Audio.PlayCollect();
			delete collectibles[i];
			collectibles.erase(collectibles.begin() + i);
			player->AddPoints(1);
			std::string score = "Score : " + std::to_string(player->GetScore());
			m_UIManage.ShowScore(score);
		}
		//Erase if out of bounds
		else if (collectibles[i]->GetPosition().y > m_windowSize.y)
		{
			delete collectibles[i];
			collectibles.erase(collectibles.begin() + i);		
		}

	}
}

bool Game::CheckIfGameOver()
{
	if (player->GetRadius() >= PLAYER_MAX_SIZE)
	{
		m_Audio.PlayGameOver();
		m_UIManage.ShowGameOverText();
		m_State = GameState::End;
		obstacles.clear();
		collectibles.clear();
		return true;
	}
	else
		return false;
}

void Game::LoseAndReborn()
{
	if (!CheckIfGameOver())
	{
		m_Audio.PlayHit();
		m_UIManage.ShowRebornText();
		m_State = GameState::Lose;

		for (auto& c : collectibles)
		{
			delete c;
		}
		for (auto& o : obstacles)
		{
			delete o;
		}
		obstacles.clear();
		collectibles.clear();
	
		float newRadius = player->GetRadius() + 5;
		player->SetRadius(newRadius);
		player->SetOrigin(newRadius, newRadius);
		player->SetPosition(sf::Vector2f(m_windowSize.x / 2, m_windowSize.y - 50));

	}
}

void Game::Update()
{
	if (m_State!= GameState::Playing)
		return;

	UpdateObstacles();
	UpdateCollectibles();

	/*AI function - development in progress*/
	//player->MoveToCollect(collectibles, obstacles, m_windowSize, m_Timer->GetDeltaTime());

	player->Move(m_Timer->GetDeltaTime());
	player->CheckWindowBounds(m_windowSize);

	if (m_Timer->TriggerLevelUp() && currentConfig.increaseDifficulty)
	{
		currentConfig.collectibleSpeed += 30.0f;
		currentConfig.obstacleSpeed += 30.0f;
		m_Timer->SetCollectibleSpawnTime(m_Timer->GetCollectibleSpawnTime() - 0.05f);
		m_Timer->SetObstacleSpawnTime(m_Timer->GetObstacleSpawnTime() - 0.05f);
		player->SetSpeed(player->GetSpeed() + 30.0f);
		
	}
	
}

void Game::Render(sf::RenderTarget& target)
{
	target.clear();
	m_UIManage.Draw(target);
	for (auto& c : collectibles)
	{
		c->Draw(target);
	}
	for (auto& o : obstacles)
	{
		o->Draw(target);
	}
	//player->DrawBounds(target); - debug colliders for AI part
	player->Draw(target);

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
		ImGui::SliderInt("NbrMaxCollectible", &tempConfig.nbrMaxCollectible, 1 , 15);
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
		player->SetSpeed(currentConfig.playerSpeed);
		player->SetRadius(currentConfig.playerRadius);
	}
	ImGui::SameLine();
	if (ImGui::Button("Reset initial parameters "))
	{
		currentConfig = initConfig; 		
		tempConfig = initConfig;

		m_Timer->SetCollectibleSpawnTime(currentConfig.collectibleSpawnTime);
		m_Timer->SetObstacleSpawnTime(currentConfig.obstacleSpawnTime);
		player->SetSpeed(currentConfig.playerSpeed);
		player->SetRadius(currentConfig.playerRadius);
	}
	ImGui::SameLine();
	if (ImGui::Button("Get current parameters"))
	{
		if (!obstacles.empty())
		currentConfig.obstacleSpeed = obstacles.back()->GetSpeed();
		if (!collectibles.empty())
		currentConfig.collectibleSpeed = collectibles.back()->GetSpeed();

		currentConfig.obstacleSpawnTime = m_Timer->GetObstacleSpawnTime();
		currentConfig.collectibleSpawnTime = m_Timer->GetCollectibleSpawnTime();
		currentConfig.playerRadius = player->GetRadius();
		currentConfig.playerSpeed = player->GetSpeed();

		tempConfig = currentConfig;
	}

	ImGui::End();
}

