#include "stdafx.h"
#include "Collectible.h"

static const float COLLECTIBLE_RADIUS{ 20.0f };

Collectible::Collectible(float speed)
{
	m_triangle = new sf::CircleShape(COLLECTIBLE_RADIUS,3);
	m_shape = m_triangle;
	m_triangle->setFillColor(sf::Color::Green);	
	m_triangle->setPosition(0,0);
	m_speed = speed;
}

Collectible::~Collectible()
{
	delete m_triangle;
	m_triangle = nullptr;
	m_shape = nullptr;
}


void Collectible::Move(float time)
{
	m_triangle->move(0.f, m_speed * time);
}

void Collectible::SetSpeed(float newSpeed)
{
	m_speed = newSpeed;
}

float Collectible::GetSpeed() const
{
	return m_speed;
}

float Collectible::GetRadius() const
{
	return m_triangle->getRadius();
}



