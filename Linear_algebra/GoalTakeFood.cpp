#include "GoalTakeFood.h"
#include "VehicleGoalBehavior.h"


GoalTakeFood::GoalTakeFood(VehicleGoalBehavior* vehicle) :
	Goal(vehicle)
{}


GoalTakeFood::~GoalTakeFood()
= default;

void GoalTakeFood::activate()
{
	_status = Goal::ACTIVE;
}

int GoalTakeFood::process()
{
	_vehicle->addFood(_food->take(_vehicle->getTransferRate()));

	if (_vehicle->isFoodFull())
		_status = Goal::COMPLETE;

	return _status;
}

void GoalTakeFood::terminate()
{
	_status = Goal::COMPLETE;
}

void GoalTakeFood::setFood(Food* food)
{
	_food = food;
}
