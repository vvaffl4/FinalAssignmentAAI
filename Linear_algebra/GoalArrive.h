#ifndef GOALARRIVE_H
#define GOALARRIVE_H
#pragma once

#include "Goal.h"
#include "Vector2D.h"

class GoalArrive : public Goal
{
private:
	Vector2D _destination;
public:
	GoalArrive(VehicleGoalBehavior* _vehicle);
	~GoalArrive();
	void activate() override;
	int process() override;
	void terminate() override;
	void setDestination(const Vector2D& destination);
};

#endif //GOALARRIVE_H