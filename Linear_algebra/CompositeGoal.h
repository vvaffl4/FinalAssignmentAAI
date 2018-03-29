#ifndef COMPOSITEGOAL_H
#define COMPOSITEGOAL_H
#pragma once

#include "Goal.h"
#include <list>

class CompositeGoal : public Goal
{
private:
	std::list<Goal*> _goalList;

public:
	CompositeGoal(Vehicle* vehicle);
	~CompositeGoal();
	int processSubgoals();
	void removeAllSubgoals();
	void addNextSubgoal(Goal* goal);
};

#endif //COMPOSITEGOAL_H