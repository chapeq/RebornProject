#pragma once
#include <Player.h>
#include <Obstacle.h>
#include <Collectible.h>
#include <vector>

class Game
{
public:
	Game();
	virtual ~Game();

	const bool IsRunning() const;
	void Update();
	void Render();

private:
	sf::RenderWindow m_window;

	float obstacleSpawnTimer;
	float obstacleSpawnTimerMax;
	float collectibleSpawnTimer;
	float collectibleSpawnTimerMax;
	bool isPause;

	Player *player;
	std::vector<Obstacle*> obstacles;
	std::vector<Collectible*> collectibles;

	void EventHandler();
	void UpdateObstacles();
	void UpdateCollectibles();
	void SpawnObstacles();
	void SpawnCollectibles();
	void Restart();

};

