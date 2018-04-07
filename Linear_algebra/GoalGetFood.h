#ifndef GOALGETFOOD_H
#define GOALGETFOOD_H
#pragma once
#include "CompositeGoal.h"


class GoalGetFood : public CompositeGoal
{
public:
	GoalGetFood(VehicleGoalBehavior* vehicle);
	~GoalGetFood();
	void activate() override;
	int process() override;
	void terminate() override;
};

#endif //GOALGETFOOD_H