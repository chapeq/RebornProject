#include "stdafx.h"
#include "Item.h"

static float SPEED_ITEMS{ 300.0f }; 
float Item::speed = SPEED_ITEMS;

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
	m_shape->move(0.f, speed * time);
}

void Item::SetPosition(sf::Vector2f pos)
{
	m_shape->setPosition(pos);
}

sf::Vector2f Item::GetPosition() const
{
	return m_shape->getPosition();
}
