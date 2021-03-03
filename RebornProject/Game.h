#pragma once
#include <Player.h>
#include <Obstacle.h>

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
	sf::Event m_ev;

	Player *player;
	Obstacle *obst;
};

