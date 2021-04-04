#pragma once
#include "Item.h"

class Obstacle : public Item
{
public:
	Obstacle(float speed);
	~Obstacle();

	void Move(float time);
	sf::Vector2f GetSize() const;

private:
	sf::RectangleShape* m_rect;
};

