#pragma once
class Item  
{
public:
	Item();
	~Item();
	
	void Draw(sf::RenderTarget& target);
	const sf::FloatRect getBounds() const;

	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition() const;

protected:
	sf::Shape* m_shape; 
};
 
