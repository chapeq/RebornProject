#include <stdafx.h>
#include <Player.h>

static const float PLAYER_START_RADIUS{ 20.0f };

Player::Player()
{
	m_cercle.setRadius(PLAYER_START_RADIUS);
	m_cercle.setOrigin(PLAYER_START_RADIUS, PLAYER_START_RADIUS);
	m_cercle.setFillColor(sf::Color::Cyan);
	m_cercle.setPosition(0,0);

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
	if (m_cercle.getGlobalBounds().left <= 0.f)
	{
		m_cercle.setPosition(m_cercle.getRadius(), m_cercle.getPosition().y);
	}
	
	if (m_cercle.getGlobalBounds().left + m_cercle.getGlobalBounds().width >= target.getSize().x)
	{
		m_cercle.setPosition(target.getSize().x -
			m_cercle.getRadius(), m_cercle.getPosition().y);
	}

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

void Player::SetOrigin(float x, float y)
{
	m_cercle.setOrigin(x, y);
}

void Player::SetPosition(sf::Vector2f pos)
{
	m_cercle.setPosition(pos);
}

int Player::GetScore()
{
	return score;
}

void Player::AddPoints(int points)
{
	score += points;
}