#ifndef GOALTHINK_H
#define GOALTHINK_H
#pragma once

#include "CompositeGoal.h"

class GoalThink : public CompositeGoal
{
public:
	GoalThink(VehicleGoalBehavior* vehicle);
	~GoalThink();
	void activate() override;
	int process() override;
	void terminate() override;
};

#endif //GOALTHINK_H