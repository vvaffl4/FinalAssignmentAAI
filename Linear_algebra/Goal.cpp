#include "Goal.h"



Goal::Goal(VehicleGoalBehavior* vehicle) :
	_vehicle(vehicle)
{}


Goal::~Goal()
= default;

bool Goal::handleMessages(Telegram& telegram) const
{
	return true;
}

void Goal::activate()
{
	_status = Goal::ACTIVE;
}

bool Goal::isActive() const
{
	return _status == Goal::ACTIVE;
}

bool Goal::isUnactive() const
{
	return _status == Goal::INACTIVE;
}

bool Goal::isComplete() const
{
	return _status == Goal::COMPLETE;
}

bool Goal::hasFailed() const
{
	return _status == Goal::FAILED;
}
