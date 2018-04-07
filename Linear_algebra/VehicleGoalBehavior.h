#ifndef VEHICLEGOALBEHAVIOR_H
#define VEHICLEGOALBEHAVIOR_H
#pragma once

#include "Vehicle.h"
#include "GoalThink.h"

class VehicleGoalBehavior : public Vehicle
{
protected:
	GoalThink*	_behavior;
	float		_gold = 0;
	float		_food = 5.0f;
	float		_transferRate = 0.1f;

public:
	VehicleGoalBehavior();
	VehicleGoalBehavior(Environment* environment, SDL_Renderer* gRenderer);
	~VehicleGoalBehavior();
	void update(double delta) override;
	void addGold(float gold);
	float takeGold(float amount);
	bool isFull() const;
	bool empty();
	float getTransferRate() const;
	void addFood(float food);
	bool isFoodFull() const;
	bool isFoodLow() const;
	void takeFood(float food);
};

#endif //VEHICLEGOALBEHAVIOR_H