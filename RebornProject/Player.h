#pragma once

class Player 
{
public:
	Player(float positionX, float positionY, int radius);
	~Player();

	void Move(float speed);
	const sf::CircleShape getShape() const;
	void Draw(sf::RenderTarget& target);
	
private:
	sf::CircleShape m_cercle;
	
};