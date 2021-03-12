#include "WanderBehaviour.h"
#include <vector>
#include "Agent.h"

WanderBehaviour::WanderBehaviour()
{
	m_target = nullptr;
	m_circleRadius = 5;
}

WanderBehaviour::WanderBehaviour(Agent* agent, float circleRadius)
{
	//I need to first think of a radius to get the "circle" at 0,0 (world position).
	//Then pick a number between 0 and the radius of the circle for the x and y 
	//to create a vector and normalize it. After this I need to find a point (higher
	//on the y axis) infront of the player and add the world positions of both circles
	//together to get the vector we want to head to.

	m_circleRadius = circleRadius;
	m_target = agent;

	//Create circle
	
	//Created a rendom point

	//Calculate the new circle center as it is in WorldPosition
	
	//I want to seek the randPoint next BEFORE ANYTHING ELSE

	//Calculate the displacement force

	//Randomly change the vector direction 
	//by making it change its current angle


	//Change wanderAngle just a bit, so it won't
	//have the same value in the next game frame


	//Finally calculate and return the wander force

}

//forward * preferred distance
//add player worldPosition to worldposition then multiply be previous one
//just get the circles position relative to the player and add that to the players worldPosition
//This is how you get the circle displace from the player

void WanderBehaviour::setAngle()
{
	
}

MathLibrary::Vector2 WanderBehaviour::calculateForce(Agent* agent)
{
	//Creating a random x and y
	float x = rand() ;
	float y = rand();
	//Find circle center of offset circle
	agent->getWorldPosition() + MathLibrary::Vector2(0, 5);
	//Created a rendom point
	MathLibrary::Vector2 randPoint = MathLibrary::Vector2(cos((double)rand()), sin((double)rand()));
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(randPoint - agent->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();
	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 wanderForce = desiredVelocity - agent->getVelocity();

	return wanderForce;
}

void WanderBehaviour::update(Agent* agent, float deltatime)
{
	//If the agent isn't null, calculate a new force and add it to the agent
	if (agent)
		agent->addForce(calculateForce(agent));

}
