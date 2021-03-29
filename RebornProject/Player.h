#pragma once
#include "Item.h"

class Player : public Item
{
public:
	Player();
	~Player();

	void Move(float time);
	void CheckWindowBounds(sf::Vector2f windowSize);
	void AddPoints(int points);
	void SetRadius(float newRad);
	void SetOrigin(float x, float y);
	float GetRadius()const;
	int GetScore() const;
	void SetSpeed(float newSpeed);
	float GetSpeed()const;

private:
	sf::CircleShape* m_cercle;
	int score;
	float speed; 
	
};