#pragma once
#include "Behaviour.h"
#include <Vector2.h>
class WanderBehaviour : public Behaviour
{
public:
	WanderBehaviour();
	void setAngle();
	void update(Agent* agent, float deltatime) override;
private:
	Agent* m_target;
	float m_wanderForce;
};
