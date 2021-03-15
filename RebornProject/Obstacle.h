#pragma once
#include "Item.h"

class Obstacle : public Item
{
public:
	Obstacle();
	~Obstacle();

	sf::Vector2f getSize() const;
		
private:
	sf::RectangleShape* m_rect;
	
};

