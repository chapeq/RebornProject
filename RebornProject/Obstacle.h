#pragma once
#include <Player.h>

class Obstacle 
{
public:
	Obstacle(float positionX, float positionY);
	~Obstacle();

	const sf::FloatRect getBounds() const;
	void Draw(sf::RenderTarget& target);
	void Move(float speed);
	bool IsCollidingPlayer(Player *player);

private:
	sf::RectangleShape m_rect;
	
};

