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

const sf::FloatRect Collectible::getBounds() const
{
	return m_triangle.getGlobalBounds();
}

void Collectible::Move(float speed)
{
	m_triangle.move(0.f, speed);
}

bool Collectible::IsCollidingPlayer(Player *player)
{
	return player->getBounds().intersects(m_triangle.getGlobalBounds());
}

