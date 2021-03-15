#include "stdafx.h"
#include "Collectible.h"

static const float COLLECTIBLE_RADIUS{ 20.0f };

Collectible::Collectible()
{
	m_triangle = new sf::CircleShape(COLLECTIBLE_RADIUS,3);
	m_shape = m_triangle;
	m_triangle->setFillColor(sf::Color::Green);	
	m_triangle->setPosition(0,0);
}

Collectible::~Collectible()
{
}

float Collectible::GetRadius() const
{
	return m_triangle->getRadius();
}


