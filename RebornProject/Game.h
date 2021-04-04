#pragma once
#include "GameEngine.h"
#include "Player.h"
#include "Obstacle.h"
#include "Collectible.h"
#include "Config.h"
#include <vector>

class Game : public GameEngine
{
public:
	Game();
	virtual ~Game();

	void Update() override;
	void Render(sf::RenderTarget& target) override;
	void RenderDebugMenu(sf::RenderTarget& target) override;

private:
	Parameters initConfig;
	Parameters currentConfig;
	Parameters tempConfig;
	Player* player;
	std::vector<Obstacle*> obstacles;
	std::vector<Collectible*> collectibles;

	void UpdateObstacles();
	void UpdateCollectibles();
	void SpawnObstacles();
	void SpawnCollectibles();
	void CheckObstacleSpawn();
	void CheckCollectibleSpawn();
	void LoseAndReborn();
	bool CheckIfGameOver();
};

