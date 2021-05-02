#include <stdafx.h>
#include <Player.h>

static const float AI_SPEED{ 3.0f };

Player::Player(float speed, float radius)
{
	m_cercle = new sf::CircleShape(radius);
	m_shape = m_cercle;
	m_cercle->setOrigin(radius, radius);
	m_cercle->setFillColor(sf::Color::Cyan);
	m_cercle->setPosition(0, 0);
	m_speed = speed;
	m_score = 0;
	m_speedAI = AI_SPEED;
	
	// Colliders for AI part
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


/**** AI Development part - WorkInProgress ****/

/*
Simulate obstacles & collectibles move at deltaTime/10
Simulate player move to next collectible at deltaTime/10
Check if will collide
 - if no futur collision -> move player to collectible at deltaTime
 - if futur collision ->
		- Don't move Player - Check if will collide with obstacle at deltaTime/10 :
				- if no collision -> don't move player
				- if futur collision -> Move Player at pos + size of obstacle

Last part player moving away from obstacle needs to be improve.

Actual algo : - if player is on the LEFT side on the window, player moves from its position to the RIGHT side
at position + player radius + obstacle size.
- if player is on the RIGHT side on the window, player moves from its position to the LEFT side
at position + player radius + obstacle size.
Problem : Sometimes the obstacle to avoid is on the left side of the player and the player is trying to avoiding
it by moving on the left (and vice versa), but it does not have time to avoid it.

Possible Solutions : - Move the player sooner / detect the collision sooner , so the player has time to avoid the
obstacle regardless of the direction. (FAILED to implement this solution).
- Detect on wich side of the obstacle is the collision point : if the player will collide on the left part of the
obstacle -> Move the player to the left. Conversely, if the player collide on the right side of the obstacle
-> Move it on to the right. 
 
 */


bool Player::IsCollidingObstacle(std::vector<Obstacle*> obstacles)
{
	if (obstacles.empty())
	{
		return false;
	}
	
	m_frontCollider->setSize(sf::Vector2f(m_cercle->getRadius() * 2, m_cercle->getRadius() * 6));
	m_frontCollider->setOrigin(m_frontCollider->getSize().x / 2, m_frontCollider->getSize().y);
	m_frontCollider->setPosition(m_cercle->getPosition());

	m_sideCollider->setSize(sf::Vector2f(m_cercle->getRadius() * 4, m_cercle->getRadius() * 2));
	m_sideCollider->setOrigin(m_sideCollider->getSize().x / 2, m_sideCollider->getSize().y / 2);
	m_sideCollider->setPosition(m_cercle->getPosition());

	for (int i = 0; i < obstacles.size(); i++)
	{
		if ((m_frontCollider->getGlobalBounds().intersects(obstacles[i]->GetBounds())) 
			||(m_sideCollider->getGlobalBounds().intersects(obstacles[i]->GetBounds())))
		{
			return true;	
		}
	}

	return false;
}


void Player::MoveToCollect(std::vector<Collectible*> collectibles, float time)
{
	if (collectibles.empty())
	{
		return;
	}

	float dest = collectibles[0]->GetPosition().x;
	float moveto = m_cercle->getPosition().x + (dest - m_cercle->getPosition().x) * m_speedAI * time;
	
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

	float moveto = m_cercle->getPosition().x + (pos - m_cercle->getPosition().x) * m_speedAI * time;
	m_cercle->setPosition(moveto, m_cercle->getPosition().y);
	m_frontCollider->setPosition(m_cercle->getPosition());
	m_sideCollider->setPosition(m_cercle->getPosition());
}


void Player::DrawBounds(sf::RenderTarget& target)
{
	target.draw(*m_frontCollider);
	target.draw(*m_sideCollider);
}

