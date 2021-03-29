#pragma once
#include "Item.h"

class Obstacle : public Item
{
public:
	Obstacle();
	~Obstacle();

	static float speed;

	sf::Vector2f getSize() const;
	void Move(float time);

private:
	sf::RectangleShape* m_rect;
	
};

