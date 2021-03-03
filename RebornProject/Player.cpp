#include <stdafx.h>
#include <Player.h>

Player::Player(float positionX, float positionY, int radius, sf::Color color)
{
	const auto pos = sf::Vector2f(positionX, positionY);
	const sf::Vector2f size(radius*2, radius*2);
	m_cercle.setPosition(pos);
	m_cercle.setRadius(radius);
	m_cercle.setFillColor(color);
	m_pos = pos;
	SetBoundingBox(m_pos, size);
}

Player::~Player()
{
}

void Player::Move(float speed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_cercle.move(0, -speed);
		m_pos = m_cercle.getPosition();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_cercle.move(0, speed);
		m_pos = m_cercle.getPosition();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_cercle.move(-speed, 0);
		m_pos = m_cercle.getPosition();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_cercle.move(speed, 0);
		m_pos = m_cercle.getPosition();
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(m_cercle);
}