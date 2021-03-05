#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle(float positionX, float positionY)
{
	const auto pos = sf::Vector2f(positionX, positionY);
	m_rect.setPosition(pos);
	m_rect.setSize(sf::Vector2f(70.f, 70.f));
	m_rect.setFillColor(sf::Color::Red);
	
}

Obstacle::~Obstacle()
{
}

void Obstacle::Draw(sf::RenderTarget& target)
{
	target.draw(m_rect);
}

const sf::RectangleShape Obstacle::getShape() const
{
	return m_rect;
}

void Obstacle::Move()
{
	m_rect.move(0.f, 7.f);
}

bool Obstacle::IsCollidingPlayer(Player *player)
{
	return player->getShape().getGlobalBounds().intersects(m_rect.getGlobalBounds());
}

