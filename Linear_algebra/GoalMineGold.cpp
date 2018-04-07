#include "GoalMineGold.h"

GoalMineGold::GoalMineGold(VehicleGoalBehavior* vehicle) :
	Goal(vehicle)
{}

GoalMineGold::~GoalMineGold()
{
}

void GoalMineGold::activate()
{
	_status = Goal::ACTIVE;
}

int GoalMineGold::process()
{
	_vehicle->addGold(_deposit->take(_vehicle->getTransferRate()));

	if (_deposit->empty())
		_status = Goal::COMPLETE;
	else if (_vehicle->isFull())
		_status = Goal::COMPLETE;
	return _status;
}

void GoalMineGold::terminate()
{
	_status = Goal::COMPLETE;
}

void GoalMineGold::setDeposit(Deposit* deposit)
{
	_deposit = deposit;
}
