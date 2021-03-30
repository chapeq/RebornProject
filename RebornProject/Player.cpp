#include <stdafx.h>
#include <Player.h>

Player::Player(float speed, float radius)
{
	m_cercle = new sf::CircleShape(radius);
	m_shape = m_cercle;
	m_cercle->setOrigin(radius, radius);
	m_cercle->setFillColor(sf::Color::Cyan);
	m_cercle->setPosition(0,0);
	m_speed = speed;
	m_score = 0;
}

Player::~Player()
{
	delete m_cercle;
	m_cercle = nullptr;
	m_shape = nullptr;
}

void Player::Move(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_cercle->move(-m_speed*time, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_cercle->move(m_speed*time, 0);
	
	}

}

void Player::CheckWindowBounds(sf::Vector2f windowSize)
{
	if (m_cercle->getGlobalBounds().left <= 0.f)
	{
		m_cercle->setPosition(m_cercle->getRadius(), m_cercle->getPosition().y);
	}

	if (m_cercle->getGlobalBounds().left + m_cercle->getGlobalBounds().width >= windowSize.x)
	{
		m_cercle->setPosition(windowSize.x - m_cercle->getRadius(), m_cercle->getPosition().y);
	}
}

void Player::SetRadius(float newRad)
{
	m_cercle->setRadius(newRad);
}

void Player::SetOrigin(float x, float y)
{
	m_cercle->setOrigin(x, y);
}

void Player::SetSpeed(float newSpeed)
{
	m_speed = newSpeed;
}

float Player::GetSpeed() const
{
	return m_speed;
}

float Player::GetRadius() const
{
	return m_cercle->getRadius();
}

int Player::GetScore() const
{
	return m_score;
}

void Player::AddPoints(int points)
{
	m_score += points;
}