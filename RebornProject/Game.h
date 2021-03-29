#pragma once
#include "GameEngine.h"
#include "Player.h"
#include "Obstacle.h"
#include "Collectible.h"
#include "UIManager.h"
#include <vector>

struct Parameters {
	 float collectibleSpeed;
	 float obstacleSpeed;
	 float collectibleSpawnTime;
	 float obstacleSpawnTime;
	 int nbrMaxObstacle;
	 int nbrMaxCollectible;
	 float playerSpeed;
	 float playerRadius;
};

class Game : public GameEngine
{
public:
	Game();
	virtual ~Game();

	void Update() override;
	void Render(sf::RenderTarget& target) override;
	void RenderDebugMenu(sf::RenderTarget& target) override;

private:
	
	Player player;
	Parameters init;
	std::vector<Obstacle> obstacles;
	std::vector<Collectible> collectibles;

	void initParameters();
	void UpdateObstacles();
	void UpdateCollectibles();
	void SpawnObstacles();
	void SpawnCollectibles();
	void LoseAndReborn();
	bool CheckIfGameOver();

};

