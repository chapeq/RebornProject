#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <vector>

static const float OBSTACLE_TIMER{ 1.0f };
static const float COLLECTIBLE_TIMER{ 1.0f };
static const int NBR_MAX_OBSTACLE{ 3 };
static const int NBR_MAX_COLLECTIBLE{ 6 };
static const float INCREASE_DIFFICULTY_TIME {10.f};


Game::Game() : GameEngine{}
{
	
	obstacleSpawnTimerMax = OBSTACLE_TIMER;
	obstacleSpawnTimer = obstacleSpawnTimerMax;
	collectibleSpawnTimerMax = COLLECTIBLE_TIMER;
	collectibleSpawnTimer = collectibleSpawnTimerMax;
	levelUpTimer = 0.f;

	player.SetPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 50));

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

}




void Game::SpawnObstacles()
{
	Obstacle obst ;
	float x = static_cast<float>(rand() % static_cast<int>(windowSize.x - obst.getSize().x));
	float y = -10.0f;
	obst.SetPosition(sf::Vector2f(x, y));
	obstacles.push_back(obst);
}

void Game::SpawnCollectibles()
{
	int  randNbrCol = rand() % NBR_MAX_COLLECTIBLE + 2;
	Collectible firstcol;
	float x = static_cast<float>(rand() % static_cast<int>(windowSize.x - (firstcol.GetRadius()*2)));
	float y = -10.0f;
	firstcol.SetPosition(sf::Vector2f(x, y));
	collectibles.push_back(firstcol);

	for (int i = 1; i < randNbrCol+1 ; i++)
	{
		Collectible nextcol;
		nextcol.SetPosition(sf::Vector2f(x , i * ((nextcol.GetRadius()*2) + 10.0f)));
		collectibles.push_back(nextcol);
	}
			
}

void Game::UpdateObstacles(float time)
{
	//Spawn
	int randNbrObst = rand() % NBR_MAX_OBSTACLE + 1;
	obstacleSpawnTimer += time;

	if (obstacleSpawnTimer >= obstacleSpawnTimerMax)
	{
		for (int i = 0; i < randNbrObst; i++)
		{
			SpawnObstacles();
		}
		obstacleSpawnTimer = 0.f;
	}
	

	//Update
	int cpt = 0;
	for (auto& e : obstacles)
	{
		//Move Down
		e.Move(time);

		// check player collision
		if (e.getBounds().intersects(player.getBounds()))
		{
			Restart();
		}

		//Delete if out of bounds
		if (e.GetPosition().y > windowSize.y)
		{
			//delete obstacles.at(cpt);
			obstacles.erase(obstacles.begin() + cpt);
		}

		cpt++;
	}
}


void Game::UpdateCollectibles(float time)
{
	collectibleSpawnTimer += time;
	//Spawn
	if (collectibleSpawnTimer >= collectibleSpawnTimerMax)
	{
		SpawnCollectibles();
		collectibleSpawnTimer = 0.f;
	}
	
	//Update
	for (auto& e : obstacles)
	{
		//Delete if overlap by obstacle
		for (int i = 0; i < collectibles.size(); i++)
		{
			if (collectibles[i].getBounds().intersects(e.getBounds()))
			{
				collectibles.erase(collectibles.begin() + i);
			}
		}
	}
	
	for (int i = 0; i < collectibles.size(); i++)
	{

		//Move Down
		collectibles[i].Move(time);

		//Check collision with player
		if (collectibles[i].getBounds().intersects(player.getBounds()))
		{
			collectibles.erase(collectibles.begin() + i);
			player.AddPoints(1);
			std::string score = "Score : " + std::to_string(player.GetScore());
			scoreText.setString(score);
		}
	}

	for (int i = 0; i < collectibles.size(); i++)
	{
		//Delete if out of bounds
		if (collectibles[i].GetPosition().y > windowSize.y)
		{
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
	mState = Lose;


	obstacles.clear();
	collectibles.clear();
	
	float newRadius = player.GetRadius() + 5;
	player.SetRadius(newRadius);
	player.SetOrigin(newRadius, newRadius);
	player.SetPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 50));
}


void Game::Update(float deltaTime)
{
	if (mState!= Playing)
		return;

	UpdateObstacles(deltaTime);
	UpdateCollectibles(deltaTime);

	player.Move(deltaTime);

	levelUpTimer += deltaTime;
	if (levelUpTimer >= INCREASE_DIFFICULTY_TIME)
	{
		//SPEED_ITEMS += 50.f;
		levelUpTimer = 0.f;
	}
	
}

void Game::Render(sf::RenderTarget& target)
{
	target.clear();
	target.draw(startText);
	target.draw(scoreText);
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
	ImGui::Begin("Debug Menu");
	ImGui::Text("Press F1 to close this debug menu");
	ImGui::NewLine();

	if (ImGui::CollapsingHeader("Game status"))
	{
	
		{
			ImGui::TextColored(ImVec4(0.f, 255.0f, 0.f, 1.f), "GAME IN PROGRESS");
		}
	}

	ImGui::End();
}
