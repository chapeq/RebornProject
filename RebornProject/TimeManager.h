#pragma once
class TimeManager
{
public:
	TimeManager(sf::Clock clock, float deltaTime);
	~TimeManager();

	 float collectibleSpawnTimerMax;
	 float obstacleSpawnTimerMax;

	sf::Time restartClock();
	void setDeltaTime();
	float getDeltaTime();

	bool triggerObstacleSpawn();
	bool triggerCollectibleSpawn();
	bool triggerLevelUp();
	bool IsGameOverTime();

private:
	sf::Clock clock;
	float deltaTime;

	float obstacleSpawnTimer;
	float collectibleSpawnTimer;
	float levelUpTimer;
	float GameOverTimer;
};

