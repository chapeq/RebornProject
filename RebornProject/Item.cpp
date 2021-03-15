#include "stdafx.h"
#include "Item.h"

static const float SPEED_ITEMS{ 300.0f };

Item::Item()
{
	//m_shape = nullptr;
}

Item::~Item()
{
}

void Item::Draw(sf::RenderTarget& target)
{
	target.draw(*m_shape);
}

const sf::FloatRect Item::getBounds() const
{
	return m_shape->getGlobalBounds();
}

void Item::Move(float time)
{
	m_shape->move(0.f, SPEED_ITEMS * time);
}

void Item::SetPosition(sf::Vector2f pos)
{
	m_shape->setPosition(pos);
}

sf::Vector2f Item::GetPosition() const
{
	return m_shape->getPosition();
}
