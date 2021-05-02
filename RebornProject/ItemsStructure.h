#pragma once
#include "Player.h"
#include "Obstacle.h"
#include "Collectible.h"
#include <vector>

struct GameSimulation {
	Player* player;
	std::vector<Obstacle*> obstacles;
	std::vector<Collectible*> collectibles;
};
