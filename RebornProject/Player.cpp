#include <stdafx.h>
#include <Player.h>

static const float PLAYER_START_RADIUS{ 20.0f };
static const float SPEED_PLAYER{ 500.0f };

Player::Player()
{
	m_cercle = new sf::CircleShape(PLAYER_START_RADIUS);
	m_shape = m_cercle;
	m_cercle->setOrigin(PLAYER_START_RADIUS, PLAYER_START_RADIUS);
	m_cercle->setFillColor(sf::Color::Cyan);
	m_cercle->setPosition(0,0);

	score = 0;
}

Player::~Player()
{
}

void Player::Move(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_cercle->move(-SPEED_PLAYER*time, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_cercle->move(SPEED_PLAYER*time, 0);
	
	}

}
/*
	if (m_cercle.getGlobalBounds().left <= 0.f)
	{
		m_cercle.setPosition(m_cercle.getRadius(), m_cercle.getPosition().y);
	}
	
	if (m_cercle.getGlobalBounds().left + m_cercle.getGlobalBounds().width >= target.getSize().x)
	{
		m_cercle.setPosition(target.getSize().x -
			m_cercle.getRadius(), m_cercle.getPosition().y);
	}
	*/
void Player::SetRadius(float newRad)
{
	m_cercle->setRadius(newRad);
}

void Player::SetOrigin(float x, float y)
{
	m_cercle->setOrigin(x, y);
}

float Player::GetRadius() const
{
	return m_cercle->getRadius();
}

int Player::GetScore() const
{
	return score;
}

void Player::AddPoints(int points)
{
	score += points;
}