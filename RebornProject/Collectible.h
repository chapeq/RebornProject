#pragma once
#include "Item.h"

class Collectible : public Item
{
public:
	Collectible();
	~Collectible();

	float GetRadius() const;	

private:
	sf::CircleShape* m_triangle;
	

};

