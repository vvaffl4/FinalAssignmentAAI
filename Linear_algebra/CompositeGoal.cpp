#include "CompositeGoal.h"

CompositeGoal::CompositeGoal(VehicleGoalBehavior* vehicle) :
	Goal(vehicle)
{
}

CompositeGoal::~CompositeGoal()
= default;

int CompositeGoal::processSubgoals()
{
	while(!_goalList.empty() && (_goalList.front()->isComplete() || _goalList.front()->hasFailed()))
	{
		_goalList.front()->terminate();
		delete _goalList.front();
		_goalList.pop_front();

		if(!_goalList.empty())
			_goalList.front()->activate();
	}

	if(!_goalList.empty())
	{
		const int status = _goalList.front()->process();

		if (status == Goal::COMPLETE && _goalList.size() > 1)
			_status = Goal::ACTIVE;
		else
			_status = status;
	}

	return _status;
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
