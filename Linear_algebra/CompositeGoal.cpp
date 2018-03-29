#include "CompositeGoal.h"



CompositeGoal::CompositeGoal(Vehicle* vehicle) :
	Goal(vehicle)
{
}


CompositeGoal::~CompositeGoal()
{
}

int CompositeGoal::processSubgoals()
{
//	while(_goalList.empty && ())
	return 0;
}

void CompositeGoal::removeAllSubgoals()
{
	for(auto currentSubgoal = _goalList.begin(); currentSubgoal != _goalList.end(); ++currentSubgoal)
	{
		(*currentSubgoal)->terminate();

		delete *currentSubgoal;
	}

	_goalList.clear();
}

void CompositeGoal::addNextSubgoal(Goal* goal)
{
	_goalList.push_back(goal);
}
