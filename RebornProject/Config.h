#pragma once

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

void GetInitConfig(Parameters& out);

