#pragma once
#include <Player.h>

class Collectible
{
public:
	Collectible(float positionX, float positionY);
	~Collectible();

	const sf::CircleShape getShape() const;
	void Draw(sf::RenderTarget& target);
	void Move();
	bool IsCollidingPlayer(Player* player);

private:
	sf::CircleShape m_triangle;

};

