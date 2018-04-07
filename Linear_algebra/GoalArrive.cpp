#include "GoalArrive.h"
#include "VehicleGoalBehavior.h"


GoalArrive::GoalArrive(VehicleGoalBehavior* _vehicle) :
	Goal(_vehicle)
{}


GoalArrive::~GoalArrive()
{
}

void GoalArrive::activate()
{
	_vehicle->getSteering()->setArriveActive(_destination, 1.0f);
	_vehicle->getSteering()->setObjectAdvoidanceActive(20.0f);
	_vehicle->getSteering()->setWallAvoidanceActive(20.0f);

	_status = Goal::ACTIVE;
}

int GoalArrive::process()
{
	if (Vector2D::distance(_vehicle->getPosition(), _destination) < 40)
		_status = Goal::COMPLETE;
	return _status;
}

void GoalArrive::terminate()
{
	_vehicle->getSteering()->setArriveUnactive();
	_vehicle->getSteering()->setObjectAdvoidanceUnactive();
	_vehicle->getSteering()->setWallAvoidanceUnactive();

	_status = Goal::COMPLETE;
}

void GoalArrive::setDestination(const Vector2D& destination)
{
	_destination = destination;
}
