#pragma once
#include "Item.h"

class Player : public Item
{
public:
	Player();
	~Player();

	virtual void Move(float time) override ;

	void AddPoints(int points);
	
	void SetRadius(float newRad);
	void SetOrigin(float x, float y);

	float GetRadius()const;
	int GetScore() const;

private:
	sf::CircleShape* m_cercle;
	int score;
	
};