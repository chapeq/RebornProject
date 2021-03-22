#include "stdafx.h"
#include "TimeManager.h"

static const float OBSTACLE_TIMER{ 1.0f };
static const float COLLECTIBLE_TIMER{ 1.0f };
static const float INCREASE_DIFFICULTY_TIME{ 10.f };
static const float GAMEOVER_MIN_TIME{ 1.0f };

TimeManager::TimeManager(sf::Clock clock, float deltaTime)
{
	this->clock = clock;
	this->deltaTime = deltaTime;

	obstacleSpawnTimerMax = OBSTACLE_TIMER;
	obstacleSpawnTimer = obstacleSpawnTimerMax;
	collectibleSpawnTimerMax = COLLECTIBLE_TIMER;
	collectibleSpawnTimer = collectibleSpawnTimerMax;
	levelUpTimer = 0.f;
	GameOverTimer = 0.f;

}

TimeManager::~TimeManager()
{
}

sf::Time TimeManager::restartClock()
{
	return clock.restart();
}

void TimeManager::setDeltaTime()
{
	deltaTime = clock.getElapsedTime().asSeconds();
}

float TimeManager::getDeltaTime()
{
	return deltaTime;
}

bool TimeManager::triggerObstacleSpawn()
{
	obstacleSpawnTimer += deltaTime;

	if (obstacleSpawnTimer >= obstacleSpawnTimerMax)
	{
		obstacleSpawnTimer = 0;
		return true;
	}
	else
		return false; 
}

bool TimeManager::triggerCollectibleSpawn()
{
	collectibleSpawnTimer += deltaTime;

	if (collectibleSpawnTimer >= collectibleSpawnTimerMax)
	{
		collectibleSpawnTimer = 0;
		return true;
	}
	else
		return false;
}


bool TimeManager::triggerLevelUp()
{
	levelUpTimer += deltaTime;

	if (levelUpTimer >= INCREASE_DIFFICULTY_TIME)
	{
		levelUpTimer = 0;
		return true;
	}
	else
		return false;
}

bool TimeManager::IsGameOverTime()
{
	GameOverTimer += deltaTime;

	if (GameOverTimer <= GAMEOVER_MIN_TIME)
	{
		GameOverTimer = 0;
		return true;
	}
	else
		return false;
}