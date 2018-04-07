#ifndef COMPOSITEGOAL_H
#define COMPOSITEGOAL_H
#pragma once

#include "Goal.h"
#include <list>

class CompositeGoal : public Goal
{
protected:
	std::list<Goal*> _goalList;

public:
	CompositeGoal(VehicleGoalBehavior* vehicle);
	virtual ~CompositeGoal();
	void activate() override = 0;
	int process() override = 0;
	void terminate() override = 0;
	int processSubgoals();
	void removeAllSubgoals();
	void addNextSubgoal(Goal* goal);
};

#endif //COMPOSITEGOAL_H