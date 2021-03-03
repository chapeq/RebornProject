#pragma once

class Player : public sf::Drawable, public BoxCollideable
{
public:
	Player(float positionX, float positionY, int radius, sf::Color color);
	~Player();

	void Move(float speed);
	
private:
	sf::CircleShape m_cercle;
	sf::Vector2f m_pos;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

};