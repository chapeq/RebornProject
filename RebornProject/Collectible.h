#pragma once
#include <Player.h>

class Collectible 
{
public:
	Collectible(float positionX, float positionY);
	~Collectible();

	const sf::FloatRect getBounds() const;
	void Draw(sf::RenderTarget& target);
	void Move(float speed);
	bool IsCollidingPlayer(Player* player);

private:
	sf::CircleShape m_triangle;

};

