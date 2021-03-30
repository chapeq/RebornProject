#pragma once
#include "Item.h"

class Collectible : public Item
{
public:
	Collectible(float speed);
	~Collectible();

	void Move(float time);
	void SetSpeed(float newSpeed);
	float GetSpeed() const;
	float GetRadius() const;	

private:
	sf::CircleShape* m_triangle;
	float m_speed;
	

};

