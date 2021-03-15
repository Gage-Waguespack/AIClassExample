#include "PursueBehaviour.h"
#include "Agent.h"
#include "Actor.h"

PursueBehaviour::PursueBehaviour()
{
	m_target = nullptr;
	setForceScale(10);
}

PursueBehaviour::PursueBehaviour(Actor* target, float seekForce)
{
	m_target = target;
	setForceScale(seekForce);
}

MathLibrary::Vector2 PursueBehaviour::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() + m_target->getVelocity() - agent->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();
	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}

void PursueBehaviour::update(Agent* agent, float deltatime)
{
	//If the agent isn't null, calculate a new force and add it to the agent
	if (agent)
		agent->addForce(calculateForce(agent));
}