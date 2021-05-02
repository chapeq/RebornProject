#include "stdafx.h"
#include "AI.h"

AI::AI()
{
}

AI::~AI()
{
}

bool AI::ComputeStep(GameSimulation state, float deltaTime, AIPlayerMove move)
{
	GameSimulation tempState = state;
	for (int i = 0; i < tempState.obstacles.size(); i++)
	{
		tempState.obstacles[i]->Move(deltaTime);
	}

	for (int i = 0; i < tempState.collectibles.size(); i++)
	{
		tempState.collectibles[i]->Move(deltaTime);
	}
	if (move == AIPlayerMove::GoToCollect)
	{
		tempState.player->MoveToCollect(tempState.collectibles, deltaTime);
	}
	return tempState.player->IsCollidingObstacle(tempState.obstacles);
}


void  AI::MoveAI(GameSimulation currentState, sf::Vector2f windowSize, float deltaTime)
{
	float simuTime = deltaTime / 10;
	bool AICollision = false;

	AICollision = ComputeStep(currentState, simuTime, AIPlayerMove::GoToCollect);
	if (!AICollision)
	{
		currentState.player->MoveToCollect(currentState.collectibles, deltaTime);
	}
	else
	{
		AICollision = ComputeStep(currentState, simuTime, AIPlayerMove::Stay);
		if (AICollision)
		{
			currentState.player->AvoidObstacle(currentState.obstacles, windowSize, deltaTime);
		}
	}
}