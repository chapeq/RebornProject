#pragma once

class Player 
{
public:
	Player();
	~Player();

	void Move(float speed);
	const sf::FloatRect getBounds() const;
	void Draw(sf::RenderTarget& target);
	void SetPosition(sf::Vector2f pos);

	void SetRadius(float newRad);
	float GetRadius();
	void SetOrigin(float x, float y);
	void AddPoints(int points);
	int GetScore();


private:
	sf::CircleShape m_cercle;
	int score;
	
};