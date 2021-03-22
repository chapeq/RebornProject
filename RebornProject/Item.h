#pragma once
class Item  
{
public:
	Item();
	~Item();
	static float speed; // pb acces parametres
	void Draw(sf::RenderTarget& target);
	const sf::FloatRect getBounds() const;
	virtual void Move(float time);
	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition() const;


protected:
	sf::Shape* m_shape; 

};
 
