#include "stdafx.h"
#include "Obstacle.h"

static const sf::Vector2f OBSTACLE_SIZE{ 70.f,70.f };

Obstacle::Obstacle()
{
	m_rect = new sf::RectangleShape(OBSTACLE_SIZE);
	m_shape = m_rect;
	m_rect->setFillColor(sf::Color::Red);
	m_rect->setPosition(0,0);	
}

Obstacle::~Obstacle()
{
}

sf::Vector2f Obstacle::getSize() const
{
	return m_rect->getSize();
}
