#include "stdafx.h"
#include "Collectible.h"

static const float COLLECTIBLE_RADIUS{ 20.0f };
static const float COLLECTIBLE_SPEED{ 300.0f };
float Collectible::speed = COLLECTIBLE_SPEED;

Collectible::Collectible()
{
	m_triangle = new sf::CircleShape(COLLECTIBLE_RADIUS,3);
	m_shape = m_triangle;
	m_triangle->setFillColor(sf::Color::Green);	
	m_triangle->setPosition(0,0);
}

Collectible::~Collectible()
{
	//pb delete m_shape
}

float Collectible::GetRadius() const
{
	return m_triangle->getRadius();
}


void Collectible::Move(float time)
{
	m_triangle->move(0.f, speed * time);
}

