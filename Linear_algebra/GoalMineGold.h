#ifndef GOALMINEGOLD_H
#define GOALMINEGOLD_H
#pragma once

#include "Goal.h"
#include "VehicleGoalBehavior.h"

class GoalMineGold : public Goal
{
protected:
	Deposit* _deposit = nullptr;
public:
	GoalMineGold(VehicleGoalBehavior* vehicle);
	~GoalMineGold();
	void activate() override;
	int process() override;
	void terminate() override;
	void setDeposit(Deposit* deposit);
};

#endif //GOALMINEGOLD_H