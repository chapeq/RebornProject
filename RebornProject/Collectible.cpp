#include "stdafx.h"
#include "Collectible.h"

Collectible::Collectible(float positionX, float positionY)
{
	const auto pos = sf::Vector2f(positionX, positionY);
	m_triangle.setPosition(pos);
	m_triangle.setRadius(20.f);
	m_triangle.setPointCount(3);
	m_triangle.setFillColor(sf::Color::Green);	
}

Collectible::~Collectible()
{
}

void Collectible::Draw(sf::RenderTarget& target)
{
	target.draw(m_triangle);
}

const sf::CircleShape Collectible::getShape() const
{
	return m_triangle;
}

void Collectible::Move()
{
	m_triangle.move(0.f, 7.f);
}

bool Collectible::IsCollidingPlayer(Player *player)
{
	return player->getShape().getGlobalBounds().intersects(m_triangle.getGlobalBounds());
}

