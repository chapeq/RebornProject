#pragma once
#include "GameEngine.h"
#include "Player.h"
#include "Obstacle.h"
#include "Collectible.h"
#include <vector>

class Game : public GameEngine
{
public:
	Game();
	virtual ~Game();

	void Update(float deltaTime) override;
	void Render(sf::RenderTarget& target) override;
	void RenderDebugMenu(sf::RenderTarget& target) override;

private:
	float obstacleSpawnTimer;
	float obstacleSpawnTimerMax;
	float collectibleSpawnTimer;
	float collectibleSpawnTimerMax;
	float levelUpTimer;

	Player player;
	std::vector<Obstacle> obstacles;
	std::vector<Collectible> collectibles;

	sf::Font fontStart;
	sf::Font fontScore;
	sf::Font fontGameOver;
	sf::Text scoreText;
	sf::Text startText;
	sf::Text gameOverText;

	void UpdateObstacles(float time);
	void UpdateCollectibles(float time);
	void SpawnObstacles();
	void SpawnCollectibles();
	void Restart();

};

