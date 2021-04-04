#include "stdafx.h"
#include "Obstacle.h"

static const sf::Vector2f OBSTACLE_SIZE{ 70.f,70.f };

Obstacle::Obstacle(float speed)
{
	m_rect = new sf::RectangleShape(OBSTACLE_SIZE);
	m_shape = m_rect;
	m_rect->setFillColor(sf::Color::Red);
	m_rect->setPosition(0,0);	
	m_rect->setOrigin(OBSTACLE_SIZE.x / 2, OBSTACLE_SIZE.y / 2);
	m_speed = speed;
}

Obstacle::~Obstacle()
{
	delete m_rect;
	m_rect = nullptr;
	m_shape = nullptr;
}


void Obstacle::Move(float time)
{
	m_rect->move(0.f, m_speed * time);
}


sf::Vector2f Obstacle::GetSize() const
{
	return m_rect->getSize();
}

