#include "stdafx.h"
#include "TimeManager.h"
#include <iostream>

static const float INCREASE_DIFFICULTY_TIME{ 10.f };

TimeManager::TimeManager(sf::Clock clock, float deltaTime)
{
	m_clock = clock;
	m_deltaTime = deltaTime;

	m_collectibleSpawnTime = 0.0f;
	m_obstacleSpawnTime = 0.0f;
	m_collectibleTimer = 0.0f;
	m_obstacleTimer = 0.0f;
	m_levelUpTimer = 0.0f;
}

TimeManager::~TimeManager()
{
}

sf::Time TimeManager::RestartClock()
{
	return m_clock.restart();
}

void TimeManager::SetDeltaTime()
{
	m_deltaTime = m_clock.getElapsedTime().asSeconds();
}

float TimeManager::GetDeltaTime()
{
	return m_deltaTime;
}

bool TimeManager::TriggerObstacleSpawn()
{
	m_obstacleTimer += m_deltaTime;

	if (m_obstacleTimer >= m_obstacleSpawnTime)
	{
		m_obstacleTimer = 0;
		return true;
	}
	else
		return false;
}

bool TimeManager::TriggerCollectibleSpawn()
{
	m_collectibleTimer += m_deltaTime;

	if (m_collectibleTimer >= m_collectibleSpawnTime)
	{
		m_collectibleTimer = 0;
		return true;
	}
	else
		return false;
}


bool TimeManager::TriggerLevelUp()
{
	m_levelUpTimer += m_deltaTime;

	if (m_levelUpTimer >= INCREASE_DIFFICULTY_TIME)
	{
		m_levelUpTimer = 0;
		return true;
	}
	else
		return false;
}


void TimeManager::SetCollectibleSpawnTime(float newTime)
{
	m_collectibleSpawnTime = newTime;
}

void TimeManager::SetObstacleSpawnTime(float newTime)
{
	m_obstacleSpawnTime = newTime;
}

float TimeManager::GetCollectibleSpawnTime() const
{
	return m_collectibleSpawnTime;
}

float TimeManager::GetObstacleSpawnTime() const
{
	return m_obstacleSpawnTime;
}