#pragma once
#include "GameEngine.h"
#include "Config.h"
#include "AI.h"

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
	AI aiPlayer; 
	
	void UpdateObstacles();
	void UpdateCollectibles();
	void SpawnObstacles();
	void SpawnCollectibles();
	void CheckObstacleSpawn();
	void CheckCollectibleSpawn();
	void LoseAndReborn();
	bool CheckIfGameOver();

};

