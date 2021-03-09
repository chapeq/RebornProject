#pragma once
#include <Player.h>

class Obstacle 
{
public:
	Obstacle();
	~Obstacle();

	const sf::FloatRect getBounds() const;
	sf::Vector2f getSize() const;
	void SetPosition(float x, float y);
	sf::Vector2f GetPosition();
	void Draw(sf::RenderTarget& target);
	void Move(float speed);
	
private:
	sf::RectangleShape m_rect;
	
};

