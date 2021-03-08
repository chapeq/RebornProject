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

const sf::FloatRect Obstacle::getBounds() const
{
	return m_rect.getGlobalBounds();
}

void Obstacle::Move(float speed)
{
	m_rect.move(0.f, speed);
}

bool Obstacle::IsCollidingPlayer(Player *player)
{
	return player->getBounds().intersects(m_rect.getGlobalBounds());
}

