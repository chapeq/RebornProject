#pragma once

class Player 
{
public:
	Player(float positionX, float positionY, int radius);
	~Player();

	void Move(float speed);
	const sf::FloatRect getBounds() const;
	void Draw(sf::RenderTarget& target);

	void SetRadius(float newRad);
	float GetRadius();
	void AddPoints(int points);
	int GetScore();


private:
	sf::CircleShape m_cercle;
	int score;
	
};