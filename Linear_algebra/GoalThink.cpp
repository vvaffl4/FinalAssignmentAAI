#include "GoalThink.h"
#include "GoalWander.h"
#include "GoalGetGold.h"
#include "GoalGetFood.h"
#include "VehicleGoalBehavior.h"


GoalThink::GoalThink(VehicleGoalBehavior* vehicle) :
	CompositeGoal(vehicle)
{}


GoalThink::~GoalThink()
= default;

void GoalThink::activate()
{
	Goal* goalGetGold = new GoalGetFood(_vehicle);
	_goalList.push_back(goalGetGold);
	goalGetGold->activate();
}

int GoalThink::process()
{
	const int status = processSubgoals();

	if(status == Goal::COMPLETE && _goalList.empty())
	{
		if(_vehicle->isFoodLow())
		{
			_goalList.push_back(new GoalGetFood(_vehicle));
		}
		else
		{
			const int random = rand() % 2;

			switch(random)
			{
			case 0: 
				_goalList.push_back(new GoalGetGold(_vehicle));
				break;
			case 1:
				_goalList.push_back(new GoalWander(_vehicle));
				break;
			}
		}

		_goalList.front()->activate();
	}

	return status;
}

void GoalThink::terminate()
{
	_goalList.front()->terminate();
}
