#ifndef GOALTAKEFOOD_H
#define GOALTAKEFOOD_H
#pragma once
#include "Goal.h"
#include "Food.h"


class GoalTakeFood : public Goal
{
private:
	Food* _food;

public:
	GoalTakeFood(VehicleGoalBehavior* vehicle);
	~GoalTakeFood();
	void activate() override;
	int process() override;
	void terminate() override;
	void setFood(Food* food);
};

#endif //GOALTAKEFOOD_H