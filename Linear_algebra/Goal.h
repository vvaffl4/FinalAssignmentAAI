#ifndef GOAL_H
#define GOAL_H
#pragma once

#include "Telegram.h"
#include "Vehicle.h"

class Goal
{
private:
	Vehicle * _vehicle;
public:
	Goal(Vehicle* vehicle);
	~Goal();
	virtual void activate() = 0;
	virtual int process() = 0;
	virtual void terminate() = 0;
	bool handleMessages(Telegram& telegram);
	bool isComplete();
};

#endif //GOAL_H