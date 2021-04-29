#include <stdafx.h>
#include <Player.h>
#include <iostream>

Player::Player(float speed, float radius)
{
	m_cercle = new sf::CircleShape(radius);
	m_shape = m_cercle;
	m_cercle->setOrigin(radius, radius);
	m_cercle->setFillColor(sf::Color::Cyan);
	m_cercle->setPosition(0, 0);
	m_speed = speed;
	m_score = 0;

	// Colliders for AI part - in development
	m_frontCollider = new sf::RectangleShape(sf::Vector2f(m_cercle->getRadius() * 2, m_cercle->getRadius() * 6));
	m_frontCollider->setOrigin(m_frontCollider->getSize().x / 2, m_frontCollider->getSize().y);
	m_frontCollider->setPosition(m_cercle->getPosition());

	m_sideCollider = new sf::RectangleShape(sf::Vector2f(m_cercle->getRadius() * 4, m_cercle->getRadius() * 2));
	m_sideCollider->setOrigin(m_sideCollider->getSize().x / 2, m_sideCollider->getSize().y / 2);
	m_sideCollider->setPosition(m_cercle->getPosition());
}

Player::~Player()
{
	delete m_cercle;
	m_cercle = nullptr;
	m_shape = nullptr;
}

void Player::Move(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_cercle->move(-m_speed * time, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_cercle->move(m_speed * time, 0);

	}
}

void Player::CheckWindowBounds(sf::Vector2f windowSize)
{
	if (m_cercle->getGlobalBounds().left <= 0.f)
	{
		m_cercle->setPosition(m_cercle->getRadius(), m_cercle->getPosition().y);
	}

	if (m_cercle->getGlobalBounds().left + m_cercle->getGlobalBounds().width >= windowSize.x)
	{
		m_cercle->setPosition(windowSize.x - m_cercle->getRadius(), m_cercle->getPosition().y);
	}
}

void Player::SetRadius(float newRad)
{
	m_cercle->setRadius(newRad);
}

void Player::SetOrigin(float x, float y)
{
	m_cercle->setOrigin(x, y);
}


float Player::GetRadius() const
{
	return m_cercle->getRadius();
}

int Player::GetScore() const
{
	return m_score;
}

void Player::AddPoints(int points)
{
	m_score += points;
}


/**** AI Development part - in progress****/

/*
AI implementation
AI move towards collectible
Check if obstacle is at a certain distance
Move away from obstacle

solutions :
- get collectible pos and move to this pos

- use Raycast to detect obstacle, or simple line intersection
 since intersection is only on y axis
- use box collider to detect collision in front of circle then move away
- compare obstacle pos and player pos

29/04/2021
Simulate obstacles & collectibles move at deltaTime/2
Simulate player move to next collectible at deltaTime/2
Check if will collide
 - if no futur collision  -> move player to collectible at deltaTime
 - if futur collision ->
		- Don't move Player - Check if will collide with obstacle at deltaTime/2 :
				- if no collision -> don't move player
				- if futur collision -> Move Player at pos + size of obstacle
 */





bool Player::IsCollidingObstacle(std::vector<Obstacle*> obstacles)
{

	if (obstacles.empty())
	{
		return false;
	}

	bool collision = false;
	float pos = m_cercle->getPosition().x;

	m_frontCollider->setSize(sf::Vector2f(m_cercle->getRadius() * 2, m_cercle->getRadius() * 6));
	m_frontCollider->setOrigin(m_frontCollider->getSize().x / 2, m_frontCollider->getSize().y);
	m_frontCollider->setPosition(m_cercle->getPosition());

	m_sideCollider->setSize(sf::Vector2f(m_cercle->getRadius() * 4, m_cercle->getRadius() * 2));
	m_sideCollider->setOrigin(m_sideCollider->getSize().x / 2, m_sideCollider->getSize().y / 2);
	m_sideCollider->setPosition(m_cercle->getPosition());

	for (int i = 0; i < obstacles.size(); i++)
	{
		if ((m_frontCollider->getGlobalBounds().intersects(
			obstacles[i]->GetBounds())) || (m_sideCollider->getGlobalBounds().intersects(
				obstacles[i]->GetBounds())))
		{

			collision = true;
			std::cout << "Obstacle to avoid : " << obstacles[i]->GetPosition().x <<"  "<< obstacles[i]->GetPosition().y << std::endl;
		}
	}

	return collision;
}


void Player::MoveToCollect(std::vector<Collectible*> collectibles, float time)
{
	if (collectibles.empty())
	{
		return;
	}

	float dest = collectibles[0]->GetPosition().x;
	float moveto = m_cercle->getPosition().x + (dest - m_cercle->getPosition().x) * 3 * time;
	
	m_cercle->setPosition(moveto, m_cercle->getPosition().y);
	m_frontCollider->setPosition(m_cercle->getPosition());
	m_sideCollider->setPosition(m_cercle->getPosition());
	
}

void Player::AvoidObstacle(std::vector<Obstacle*> obstacles, sf::Vector2f windowSize, float time)
{
	if (obstacles.empty())
	{
		return;
	}
	float pos = m_cercle->getPosition().x;

	if (pos > windowSize.x / 2)
	{
		pos -= obstacles[0]->GetSize().x + m_cercle->getRadius();
	}
	if (pos < windowSize.x / 2)
	{
		pos += obstacles[0]->GetSize().x + m_cercle->getRadius();
	}

	float moveto = m_cercle->getPosition().x + (pos - m_cercle->getPosition().x) * 3 * time;
	m_cercle->setPosition(moveto, m_cercle->getPosition().y);
	m_frontCollider->setPosition(m_cercle->getPosition());
	m_sideCollider->setPosition(m_cercle->getPosition());

}


void Player::DrawBounds(sf::RenderTarget& target)
{
	target.draw(*m_frontCollider);
	target.draw(*m_sideCollider);
}

