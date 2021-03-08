#include <stdafx.h>
#include <Player.h>

Player::Player(float positionX, float positionY, int radius)
{
	const auto pos = sf::Vector2f(positionX, positionY);
	m_cercle.setPosition(pos);
	m_cercle.setRadius(radius);
	m_cercle.setFillColor(sf::Color::Cyan);
	score = 0;
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

const sf::FloatRect Player::getBounds() const
{
	return m_cercle.getGlobalBounds();
}

float Player::GetRadius()
{
	return m_cercle.getRadius();
}

void Player::SetRadius(float newRad)
{
	m_cercle.setRadius(newRad);
}

int Player::GetScore()
{
	return score;
}

void Player::AddPoints(int points)
{
	score += points;
}