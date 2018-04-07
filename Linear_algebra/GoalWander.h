#ifndef GOALWANDER_H
#define GOALWANDER_H
#pragma once

#include "Goal.h"

class GoalWander : public Goal
{
private:
	float _time = 0.0f;

public:
	GoalWander(VehicleGoalBehavior* vehicle);
	~GoalWander();
	void activate() override;
	int process() override;
	void terminate() override;
};

#endif // GOALWANDER_H