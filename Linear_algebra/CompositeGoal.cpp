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
//	while(_goalList.empty && _goalList.front()->isComplete() || _goalList.front()->hasFailed())
//	{
//		_goalList.front()->terminate();
//		delete _goalList.front();
//		_goalList.pop_front();
//	}
//
//	if(_goalList.empty())
//	{
//		int status = _goalList.front()->process();
//
//		if (status == completed && _goalList.size() > 1)
//			return active;
//
//		return status;
//	}
//
//	return completed;
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
