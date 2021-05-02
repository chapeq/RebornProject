#include "stdafx.h"
#include "Item.h"

Item::Item()
{
	m_shape = nullptr;
	m_speed = 0.0f;
}

Item::~Item()
{
}

void Item::Draw(sf::RenderTarget& target)
{
	target.draw(*m_shape);
}

const sf::FloatRect Item::GetBounds() const
{
	return m_shape->getGlobalBounds();
}


void Item::SetPosition(sf::Vector2f pos)
{
	m_shape->setPosition(pos);
}

sf::Vector2f Item::GetPosition() const
{
	return m_shape->getPosition();
}

void Item::SetSpeed(float newSpeed)
{
	m_speed = newSpeed;
}

float Item::GetSpeed() const
{
	return m_speed;
}
