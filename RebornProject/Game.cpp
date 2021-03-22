#include "stdafx.h"
#include "Game.h"
#include "Item.h"
#include <iostream>
#include <vector>


static const int NBR_MAX_OBSTACLE{ 3 };
static const int NBR_MAX_COLLECTIBLE{ 6 };
static const float PLAYER_MAX_SIZE{ 80.0f };

Game::Game() : GameEngine{}
{
	player.SetPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 50));
}

Game::~Game()
{

}


void Game::SpawnObstacles()
{
	Obstacle obst ;
	float x = static_cast<float>(rand() % static_cast<int>(windowSize.x - obst.getSize().x));
	float y = -10.0f; //offset
	obst.SetPosition(sf::Vector2f(x, y));
	obstacles.push_back(obst);
}

void Game::SpawnCollectibles()
{
	int  randNbrCol = rand() % NBR_MAX_COLLECTIBLE + 2;
	Collectible firstcol;
	float x = static_cast<float>(rand() % static_cast<int>(windowSize.x - (firstcol.GetRadius()*2)));
	float y = -10.0f; //offset
	firstcol.SetPosition(sf::Vector2f(x, y));
	collectibles.push_back(firstcol);
	//Spawn next collectibles with 10.f offset between each other
	for (int i = 1; i < randNbrCol+1 ; i++)
	{
		Collectible nextcol;
		nextcol.SetPosition(sf::Vector2f(x , i * ((nextcol.GetRadius()*2) + 10.0f)));
		collectibles.push_back(nextcol);
	}
			
}

void Game::UpdateObstacles()
{
	//Spawn
	int randNbrObst = rand() % NBR_MAX_OBSTACLE + 1;	

	if (timer->triggerObstacleSpawn())
	{
		for (int i = 0; i < randNbrObst; i++)
		{
			SpawnObstacles();
		}
	}
	
	//Update
	for (int i = 0; i < obstacles.size(); i++)
	{
		//Move Down
		obstacles[i].Move(timer->getDeltaTime());

		// check player collision
		if (obstacles[i].getBounds().intersects(player.getBounds()))
		{
			LoseAndReborn();
		}
		//Delete if out of bounds
		else if (obstacles[i].GetPosition().y > windowSize.y)
		{
			obstacles.erase(obstacles.begin() + i);
		}
	}
}


void Game::UpdateCollectibles()
{
	//Spaw

	if (timer->triggerCollectibleSpawn())
	{
		SpawnCollectibles();
	}
	
	//Delete if overlap by obstacle
	for (auto& e : obstacles)
	{
		for (int i = 0; i < collectibles.size(); i++)
		{
			if (collectibles[i].getBounds().intersects(e.getBounds()))
			{
				collectibles.erase(collectibles.begin() + i);
			}
		}
	}
	
	//Update
	for (int i = 0; i < collectibles.size(); i++)
	{
		//Move Down
		collectibles[i].Move(timer->getDeltaTime());

		//Check collision with player
		if (collectibles[i].getBounds().intersects(player.getBounds()))
		{
			collectibles.erase(collectibles.begin() + i);
			player.AddPoints(1);
			std::string score = "Score : " + std::to_string(player.GetScore());
			uiManage.afficheScore(score);
		}
		//Delete if out of bounds
		else if (collectibles[i].GetPosition().y > windowSize.y)
		{
			collectibles.erase(collectibles.begin() + i);
		}

	}
}

bool Game::CheckIfGameOver()
{
	if (timer->IsGameOverTime() && player.GetRadius() >= PLAYER_MAX_SIZE)
	{
		uiManage.afficheGameOverText();
		mState = GameState::End;
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
		uiManage.afficheRebornText();
		mState = GameState::Lose;

		obstacles.clear();
		collectibles.clear();

		float newRadius = player.GetRadius() + 5;
		player.SetRadius(newRadius);
		player.SetOrigin(newRadius, newRadius);
		player.SetPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 50));

	}
}


void Game::Update()
{
	if (mState!= GameState::Playing)
		return;

	UpdateObstacles();
	UpdateCollectibles();

	player.Move(timer->getDeltaTime());

	if (timer->triggerLevelUp())
	{
		Item::speed += 50.f;
	}
	
}

void Game::Render(sf::RenderTarget& target)
{
	target.clear();
	uiManage.Draw(target);
	for (auto& c : collectibles)
	{
		c.Draw(target);
	}
	for (auto& o : obstacles)
	{
		o.Draw(target);
	}
	player.Draw(target);
}

void Game::RenderDebugMenu(sf::RenderTarget& target)
{
	ImGuiIO& io = ImGui::GetIO();
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui::Begin("Parameter window");
	ImGui::NewLine();

	if (ImGui::CollapsingHeader("Obstacles and Collectibles : "))
	{
		float f0 = Item::speed;
		float f1 = timer->collectibleSpawnTimerMax;
		float f2 = timer->obstacleSpawnTimerMax;
		ImGui::InputFloat("Speed", &f0, 1.0f, 1.0f, "%.3f");
		ImGui::InputFloat("CollectibleSpawnTimer", &f1, 1.0f, 1.0f, "%.3f");
		ImGui::InputFloat("ObstacleSpawnTimer", &f2, 1.0f, 1.0f, "%.3f");
	}

	if (ImGui::CollapsingHeader("Player : "))
	{
		float f0 = player.speedPlayer;
		ImGui::InputFloat("Speed", &f0, 1.0f, 1.0f, "%.3f");
	}

	ImGui::End();
}
