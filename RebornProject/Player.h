#pragma once
#include "Item.h"
#include "Obstacle.h"
#include "Collectible.h"

class Player : public Item
{
public:
	Player(float speed, float radius);
	~Player();

	void Move(float time);
	void CheckWindowBounds(sf::Vector2f windowSize);
	void AddPoints(int points);

	void SetRadius(float newRad);
	void SetOrigin(float x, float y);
	float GetRadius()const;
	int GetScore() const;


	// AI part - in progress 
	void MoveToCollect(std::vector<Collectible*> collectibles, std::vector<Obstacle*> obstacles, sf::Vector2f windowSize, float time);
	bool IsAvoidingObstacles(std::vector<Obstacle*> obstacles, sf::Vector2f windowSize, float time);
	bool CanMove(std::vector<Obstacle*> obstacles);
	void DrawBounds(sf::RenderTarget& target);


private:
	sf::CircleShape* m_cercle;
	sf::RectangleShape* m_frontCollider;
	sf::RectangleShape* m_sideCollider;
	int m_score;
};