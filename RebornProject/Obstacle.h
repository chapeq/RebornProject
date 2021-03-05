#pragma once
#include <Player.h>

class Obstacle 
{
public:
	Obstacle(float positionX, float positionY);
	~Obstacle();

	const sf::RectangleShape getShape() const;
	void Draw(sf::RenderTarget& target);
	void Move();
	bool IsCollidingPlayer(Player *player);

private:
	sf::RectangleShape m_rect;
	
};

