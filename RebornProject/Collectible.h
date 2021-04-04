#pragma once
#include "Item.h"

class Collectible : public Item
{
public:
	Collectible(float speed);
	~Collectible();

	void Move(float time);
	float GetRadius() const;

private:
	sf::CircleShape* m_triangle;
};

