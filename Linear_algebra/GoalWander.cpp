#include "GoalWander.h"
#include "VehicleGoalBehavior.h"


GoalWander::GoalWander(VehicleGoalBehavior* vehicle) :
	Goal(vehicle),
	_time(0.0f)
{}

GoalWander::~GoalWander()
= default;

void GoalWander::activate()
{
	Goal::activate();

	_vehicle->getSteering()->setWanderActive(1.0f);
	_vehicle->getSteering()->setObjectAdvoidanceActive(20.0f);
	_vehicle->getSteering()->setWallAvoidanceActive(20.0f);
}

int GoalWander::process()
{
	_time += 0.1f;
	_vehicle->takeFood(0.01f);

	if (_time > 100)
		_status = Goal::COMPLETE;

	std::cout << "Wander time: " << _time << std::endl;

	return _status;
}

void GoalWander::terminate()
{
	_vehicle->getSteering()->setWanderUnactive();
	_vehicle->getSteering()->setObjectAdvoidanceUnactive();
	_vehicle->getSteering()->setWallAvoidanceUnactive();
}
