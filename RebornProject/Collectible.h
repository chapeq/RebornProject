#pragma once
#include "Item.h"

class Collectible : public Item
{
public:
	Collectible();
	~Collectible();

	static float speed;

	float GetRadius() const;	
	void Move(float time);

private:
	sf::CircleShape* m_triangle;
	

};

