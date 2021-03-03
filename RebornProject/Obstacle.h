#pragma once

class Obstacle : public BoxCollideable , public sf::Drawable
{
public:
	Obstacle(float positionX, float positionY, sf::Vector2f size, sf::Color color);
	~Obstacle();

private:
	sf::RectangleShape m_rect;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};

