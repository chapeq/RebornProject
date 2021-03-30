#pragma once
class TimeManager
{
public:
	TimeManager(sf::Clock clock, float deltaTime);
	~TimeManager();

	sf::Time RestartClock();

	void SetDeltaTime();
	void SetCollectibleSpawnTime(float newTime);
	void SetObstacleSpawnTime(float newTime);
	float GetDeltaTime();
	float GetCollectibleSpawnTime() const;
	float GetObstacleSpawnTime() const;

	bool TriggerObstacleSpawn();
	bool TriggerCollectibleSpawn();
	bool TriggerLevelUp();

private:
	sf::Clock m_clock;
	float m_deltaTime;

	float m_collectibleSpawnTime;
	float m_obstacleSpawnTime;
	float m_collectibleTimer;
	float m_obstacleTimer;;
	float m_levelUpTimer;
};

