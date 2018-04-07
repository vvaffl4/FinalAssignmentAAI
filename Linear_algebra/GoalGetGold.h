#ifndef GOALGETGOLD_H
#define GOALGETGOLD_H
#pragma once

#include "CompositeGoal.h"
#include "Deposit.h"

class GoalGetGold : public CompositeGoal
{
protected:
	Deposit* _deposit = nullptr;

public:
	GoalGetGold(VehicleGoalBehavior* vehicle);
	~GoalGetGold();
	void activate() override;
	int process() override;
	void terminate() override;
};

#endif //GOALGETGOLD_H