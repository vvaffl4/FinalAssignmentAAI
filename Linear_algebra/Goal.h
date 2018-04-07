#ifndef GOAL_H
#define GOAL_H
#pragma once

#include "Telegram.h"

class VehicleGoalBehavior;

class Goal
{
protected:
	VehicleGoalBehavior* _vehicle;
	char _status = 0;

public:
	static const char INACTIVE = 0;
	static const char ACTIVE = 1;
	static const char COMPLETE = 2;
	static const char FAILED = 3;

	Goal(VehicleGoalBehavior* vehicle);
	virtual ~Goal();
	virtual void activate();
	virtual int process() = 0;
	virtual void terminate() = 0;
	bool handleMessages(Telegram& telegram) const;
	bool isActive() const;
	bool isUnactive() const;
	bool isComplete() const;
	bool hasFailed() const;
};

#endif //GOAL_H