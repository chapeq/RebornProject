#include "stdafx.h"
#include "Collectible.h"

static const float COLLECTIBLE_RADIUS{ 20.0f };

Collectible::Collectible()
{
	m_triangle.setRadius(COLLECTIBLE_RADIUS);
	m_triangle.setPointCount(3);
	m_triangle.setFillColor(sf::Color::Green);	
	m_triangle.setPosition(0,0);
}

Collectible::~Collectible()
{
}

void Collectible::SetPosition(float x, float y)
{
	m_triangle.setPosition(x, y);
}

sf::Vector2f Collectible::GetPosition()
{
	return m_triangle.getPosition();
}

float Collectible::GetRadius() const
{
	return m_triangle.getRadius();
}

void Collectible::Draw(sf::RenderTarget& target)
{
	target.draw(m_triangle);
}

const sf::FloatRect Collectible::getBounds() const
{
	return m_triangle.getGlobalBounds();
}

void Collectible::Move(float speed)
{
	m_triangle.move(0.f, speed);
}


