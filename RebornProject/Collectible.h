#pragma once
#include <Player.h>

class Collectible 
{
public:
	Collectible();
	~Collectible();

	const sf::FloatRect getBounds() const;
	void SetPosition(float x, float y);
	sf::Vector2f GetPosition();
	float GetRadius() const;
	void Draw(sf::RenderTarget& target);
	void Move(float speed);

private:
	sf::CircleShape m_triangle;

};

