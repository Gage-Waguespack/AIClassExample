#include "WanderBehaviour.h"
#include <vector>

WanderBehaviour::WanderBehaviour()
{
}

WanderBehaviour::WanderBehaviour(Agent* agent)
{
	// I need to make a circle, then I need to offset the circle 
	//and calculate the center. After that I have to pick a random 
	//point, normalize it to the circles border and calculate the 
	//displacement and with that displacement, return the wander
	//force, and move to that random point and keep doing that 
	//until the enemy stops wandering (whenevever that may be).
	//Remember to obtain a randomized point and that the sum of 
	//the circle center vector and displacement is the wander force.

	//Create circle


	//offset circle


	//Calculate the circle center


	//Calculate the displacement force


	//Randomly change the vector direction 
	//by making it change its current angle


	//Change wanderAngle just a bit, so it won't
	//have the same value in the next game frame


	//Finally calculate and return the wander force

}

void WanderBehaviour::setAngle()
{
	
}

void WanderBehaviour::update(Agent* agent, float deltatime)
{

}
