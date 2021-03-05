#include <stdafx.h>
#include <Player.h>

Player::Player(float positionX, float positionY, int radius)
{
	const auto pos = sf::Vector2f(positionX, positionY);
	m_cercle.setPosition(pos);
	m_cercle.setRadius(radius);
	m_cercle.setFillColor(sf::Color::Cyan);
	
}

Player::~Player()
{
}

void Player::Move(float speed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_cercle.move(-speed, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_cercle.move(speed, 0);
	
	}
}

void Player::Draw(sf::RenderTarget& target)
{
	target.draw(m_cercle);
}

const sf::CircleShape Player::getShape() const
{
	return m_cercle;
}