#include "WanderBehaviour.h"
#include <vector>
#include "Agent.h"

WanderBehaviour::WanderBehaviour()
{
}

WanderBehaviour::WanderBehaviour(Agent* agent)
{
	//I need to first think of a radius to get the "circle" at 0,0 (world position).
	//Then pick a number between 0 and the radius of the circle for the x and y 
	//to create a vector and normalize it. After this I need to find a point (higher
	//on the y axis) infront of the player and add the world positions of both circles
	//together to get the vector we want to head to.

	//Create circle
	float x = 2;
	float y = 2;
	
	//take the x and y and turn it into a vector
	MathLibrary::Vector2 (x, y);

	//Calculate the new circle center as it is in WorldPosition


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
