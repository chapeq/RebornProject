#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <vector>


static  int NBR_MAX_OBSTACLE{ 3 };
static  int NBR_MAX_COLLECTIBLE{ 6 };
static const float PLAYER_MAX_SIZE{ 80.0f };

Game::Game() : GameEngine{}
{
	player.SetPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 50));
	initParameters();
}

Game::~Game()
{

}

void Game::initParameters()
{
	init.collectibleSpeed = Collectible::speed;
	init.obstacleSpeed = Obstacle::speed;
	init.collectibleSpawnTime = timer->collectibleSpawnTimerMax;
	init.obstacleSpawnTime = timer->obstacleSpawnTimerMax;
	init.nbrMaxObstacle = NBR_MAX_OBSTACLE;
	init.nbrMaxCollectible = NBR_MAX_COLLECTIBLE;
	init.playerSpeed = player.GetSpeed();
	init.playerRadius = player.GetRadius();
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
	int  randNbrCol = rand() % NBR_MAX_COLLECTIBLE + 1;
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
			audio.PlayCollect();
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
		audio.PlayGameOver();
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
		audio.PlayHit();
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
	player.CheckWindowBounds(windowSize);

	if (timer->triggerLevelUp())
	{
		Collectible::speed += 50.f;
		Obstacle::speed += 50.f;
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
	ImGui::Begin("Parameter window");
	ImGui::NewLine();

	static float collectibleSpeed = Collectible::speed;
	static float obstacleSpeed = Obstacle::speed;
	static float collectibleSpawnTime = timer->collectibleSpawnTimerMax;
	static float obstacleSpawnTime = timer->obstacleSpawnTimerMax;
	static int nbrMaxObstacle = NBR_MAX_OBSTACLE;
	static int nbrMaxCollectible = NBR_MAX_COLLECTIBLE;
	static float playerSpeed = player.GetSpeed();
	static float  playerRadius = player.GetRadius();
	
	if (ImGui::CollapsingHeader("Obstacles and Collectibles : "))
	{
		ImGui::SliderFloat("CollectibleSpeed", &collectibleSpeed, 100.0f, 900.0f, "%.1f");
		ImGui::SliderFloat("ObstacleSpeed", &obstacleSpeed, 100.0f, 900.0f, "%.1f");
		ImGui::SliderFloat("CollectibleSpawnTime", &collectibleSpawnTime, 0.2f, 5.0f, "%.2f");
		ImGui::SliderFloat("ObstacleSpawnTime", &obstacleSpawnTime, 0.2f, 5.0f, "%.2f");
		ImGui::SliderInt("NbrMaxCollectible", &nbrMaxCollectible, 1 , 15);
		ImGui::SliderInt("NbrMaxObstacle", &nbrMaxObstacle, 1, 10);
	}

	if (ImGui::CollapsingHeader("Player : "))
	{
		ImGui::SliderFloat("Speed", &playerSpeed, 100.0f, 900.0f, "%.1f");
		ImGui::SliderFloat("Size", &playerRadius, 10.0f, 200.0f, "%.1f");
	}
	ImGui::NewLine();

	if (ImGui::Button("Apply"))
	{
		Collectible::speed = collectibleSpeed ;
		Obstacle::speed = obstacleSpeed;
		timer->collectibleSpawnTimerMax = collectibleSpawnTime;
		timer->obstacleSpawnTimerMax = obstacleSpawnTime;
		NBR_MAX_OBSTACLE = nbrMaxObstacle;
		NBR_MAX_COLLECTIBLE = nbrMaxCollectible;
		player.SetSpeed(playerSpeed);
		player.SetRadius(playerRadius);
	}
	ImGui::SameLine();
	if (ImGui::Button("Reset"))
	{
		 collectibleSpeed = init.collectibleSpeed;
		  obstacleSpeed = init.obstacleSpeed;
		 collectibleSpawnTime = init.collectibleSpawnTime;
		 obstacleSpawnTime = init.obstacleSpawnTime;
		nbrMaxObstacle = init.nbrMaxObstacle;
		 nbrMaxCollectible = init.nbrMaxCollectible;
		 playerSpeed = init.playerSpeed;
		 playerRadius = init.playerRadius;
	}

	ImGui::End();
}

