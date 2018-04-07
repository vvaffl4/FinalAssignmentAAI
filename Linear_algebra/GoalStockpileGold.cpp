#include "GoalStockpileGold.h"
#include "VehicleGoalBehavior.h"


GoalStockpileGold::GoalStockpileGold(VehicleGoalBehavior* vehicle) :
	Goal(vehicle)
{}

GoalStockpileGold::~GoalStockpileGold()
= default;

void GoalStockpileGold::setStockpile(Stockpile* stockpile)
{
	_stockpile = stockpile;
}

void GoalStockpileGold::activate()
{
	_status = Goal::ACTIVE;
}

int GoalStockpileGold::process()
{
	_stockpile->addGold(_vehicle->takeGold(_vehicle->getTransferRate()));

	if (_vehicle->empty())
		_status = Goal::COMPLETE;

	return _status;
}

void GoalStockpileGold::terminate()
{
	_status = Goal::COMPLETE;
}
