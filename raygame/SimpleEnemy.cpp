#include "SimpleEnemy.h"
#include "SeekBehaviour.h"
#include "WanderBehaviour.h"

bool SimpleEnemy::checkTargetInSight()
{
	//Check if the target is null. If so, return false
	if (!getTarget())
		return false;

	//Find the direction vector that represent where the target is relative to the enemy
	MathLibrary::Vector2 direction = getTarget()->getWorldPosition() - getWorldPosition();

	//Find the dot product of the enemy's forward and the direction vector
	MathLibrary::Vector2::dotProduct(getTarget()->getForward(), direction);

	//Find the angle using the dot product
	float angle = (float)MathLibrary::Vector2::findAngle(getTarget()->getForward(), direction);

	//Check if that angle is greater than the enemy's viewing angle(any value you see fit is fine)
	if (angle > 2)
		//Return if the enemy saw the target (true if enemy sees player)
		return true;

	//otherwise return false
	return false;
}

void SimpleEnemy::onCollision(Actor* other)
{
	//Check to see if the enemy ran into the player
	if (getWorldPosition() == other->getWorldPosition())
	{
		//If the enemy has run into the player, deal damage to the player
		dynamic_cast<Character*>(other)->takeDamage(1);
	}
	//If the player health is less than 0, set the target to be nullptr
	if (dynamic_cast<Character*>(other)->getHealth() <= 0)
	{
		setTarget(nullptr);
	}
}

void SimpleEnemy::start()
{
	//Call base start function
	Enemy::start();

	//Set the default state of the enemy
	m_currentState = WANDER;

	//Initialize member variables
	m_seek = getBehaviour<SeekBehaviour>();
	m_wander = getBehaviour<WanderBehaviour>();

	//Set the target to be the base class target
	setTarget(Enemy::getTarget());
}

void SimpleEnemy::update(float deltaTime)
{
	//Create a switch statement for the state machine.
	//The switch should transition to the wander state if the target is not in sight
	//You can set the wander force to be whatever value you see fit but be sure to 
	//set the seek force to be 0.
	
	int x = 1;

	if (!checkTargetInSight())
		x = 1;

	else if (checkTargetInSight())
		x = 2;

	switch (x)
	{
		//default to wander
	case 1: addBehaviour(m_wander);

		//If the target is in sight, seek.
	case 2: addBehaviour(m_seek);
	}

	//The switch should transition to the seek state if the target is in sight.
	//You can set the seek force to be whatever value you see fit, but be sure to
	//set the wander force to be 0.

	Enemy::update(deltaTime);
}

void SimpleEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_seek->setTarget(target);
}
