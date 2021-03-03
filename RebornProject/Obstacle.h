#pragma once

class Obstacle 
{
public:
	Obstacle(float positionX, float positionY, sf::Vector2f size, sf::Color color);
	~Obstacle();

	const sf::RectangleShape getShape() const;
	void draw(sf::RenderTarget& target);

private:
	sf::RectangleShape m_rect;
	
};

