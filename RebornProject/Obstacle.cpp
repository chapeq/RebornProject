#include "stdafx.h"
#include "Obstacle.h"

static const sf::Vector2f OBSTACLE_SIZE{ 70.f,70.f };

Obstacle::Obstacle()
{
	m_rect.setSize(OBSTACLE_SIZE);
	m_rect.setFillColor(sf::Color::Red);
	m_rect.setPosition(0,0);	
}

Obstacle::~Obstacle()
{
}

void Obstacle::SetPosition(float x, float y)
{
	m_rect.setPosition(x, y);
}

sf::Vector2f Obstacle::GetPosition()
{
	return m_rect.getPosition();
}

void Obstacle::Draw(sf::RenderTarget& target)
{
	target.draw(m_rect);
}

const sf::FloatRect Obstacle::getBounds() const
{
	return m_rect.getGlobalBounds();
}

sf::Vector2f Obstacle::getSize() const
{
	return m_rect.getSize();
}

void Obstacle::Move(float speed)
{
	m_rect.move(0.f, speed);
}

