#pragma once
#include "ItemsStructure.h"

enum class AIPlayerMove
{
	GoToCollect,
	Stay,
	AvoidObstacle
};

class AI
{
public:
	AI();
	~AI();

	 void MoveAI(GameSimulation currentState, sf::Vector2f windowSize, float deltaTime);

private :
	 bool ComputeStep(GameSimulation state, float deltaTime, AIPlayerMove move);
		
};

