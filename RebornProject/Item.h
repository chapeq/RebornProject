#pragma once
class Item
{
public:
	Item();
	~Item();

	void Draw(sf::RenderTarget& target);
	const sf::FloatRect GetBounds() const;

	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition() const;
	void SetSpeed(float newSpeed);
	float GetSpeed()const;

protected:
	sf::Shape* m_shape;
	float m_speed;
};

