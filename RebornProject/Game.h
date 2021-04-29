#pragma once
#include "GameEngine.h"
#include "Player.h"
#include "Obstacle.h"
#include "Collectible.h"
#include "Config.h"
#include <vector>

enum class AIPlayerMove
{
	GoToCollect,
	Stay,
	AvoidObstacle
};

struct GameSimulation {
	Player* player;
	std::vector<Obstacle*> obstacles;
	std::vector<Collectible*> collectibles;
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
	Parameters initConfig;
	Parameters currentConfig;
	Parameters tempConfig;
	GameSimulation currentState;

	void UpdateObstacles();
	void UpdateCollectibles();
	void SpawnObstacles();
	void SpawnCollectibles();
	void CheckObstacleSpawn();
	void CheckCollectibleSpawn();
	void LoseAndReborn();
	bool CheckIfGameOver();
	bool ComputeStep(GameSimulation state, float deltaTime, AIPlayerMove move);
};

