#ifndef GOLDSTOCKPILE_H
#define GOLDSTOCKPILE_H
#pragma once

#include "Goal.h"
#include "Stockpile.h"

class GoalStockpileGold : public Goal
{
protected:
	Stockpile * _stockpile;

public:
	GoalStockpileGold(VehicleGoalBehavior* vehicle);
	~GoalStockpileGold();
	void activate() override;
	int process() override;
	void terminate() override;
	void setStockpile(Stockpile* stockpile);
};

#endif //GOLDSTOCKPILE_H