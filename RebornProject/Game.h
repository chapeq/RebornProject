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

	float obstSpawnTimer;
	float obstSpawnTimerMax;
	float colSpawnTimer;
	float colSpawnTimerMax;
	bool isPause;

	Player *player;
	std::vector<Obstacle*> obstacles;
	std::vector<Collectible*> collectibles;

	void EventHandler();
	void SpawnObstacles();
	void UpdateObstacles();
	void SpawnCollectibles();
	void UpdateCollectibles();

};

