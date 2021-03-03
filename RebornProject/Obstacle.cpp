#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle(float positionX, float positionY, sf::Vector2f size, sf::Color color)
{
	const auto pos = sf::Vector2f(positionX, positionY);
	m_rect.setPosition(pos);
	m_rect.setSize(size);
	m_rect.setFillColor(color);
	SetBoundingBox(pos, size);
}

Obstacle::~Obstacle()
{
}

void Obstacle::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(m_rect);
}

