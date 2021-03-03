#pragma once

class Player 
{
public:
	Player(float positionX, float positionY, int radius, sf::Color color);
	~Player();

	void Move(float speed);
	const sf::CircleShape getShape() const;
	void draw(sf::RenderTarget& target);
	
private:
	sf::CircleShape m_cercle;
	
};