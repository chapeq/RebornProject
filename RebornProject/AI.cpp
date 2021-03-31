#include "stdafx.h"
#include "AI.h"
#include <iostream>

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

 */

void MoveAI(Player* player, std::vector<Obstacle*> obstacles, 
    std::vector<Collectible*> collectibles)
{

}