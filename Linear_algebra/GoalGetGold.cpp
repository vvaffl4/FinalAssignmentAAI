#include "GoalGetGold.h"
#include "GoalArrive.h"
#include "GoalMineGold.h"
#include "GoalStockpileGold.h"


GoalGetGold::GoalGetGold(VehicleGoalBehavior* vehicle) :
	CompositeGoal(vehicle)
{}

GoalGetGold::~GoalGetGold()
= default;

void GoalGetGold::activate()
{
	Deposit* deposit = Environment::GetInstance()->getClosestAvailableDeposit(_vehicle->getPosition());
	Stockpile* stockpile = Environment::GetInstance()->getStockpile();

	GoalArrive* goalArriveDeposit = new GoalArrive(_vehicle);
	goalArriveDeposit->setDestination(deposit->getPosition());
	goalArriveDeposit->activate();
	_goalList.push_back(goalArriveDeposit);

	GoalMineGold* goalGetGold = new GoalMineGold(_vehicle);
	goalGetGold->setDeposit(deposit);
	_goalList.push_back(goalGetGold);

	GoalArrive* goalArriveStockpile = new GoalArrive(_vehicle);
	goalArriveStockpile->setDestination(stockpile->getPosition());
	_goalList.push_back(goalArriveStockpile);

	GoalStockpileGold* goalStockpileGold = new GoalStockpileGold(_vehicle);
	goalStockpileGold->setStockpile(stockpile);
	_goalList.push_back(goalStockpileGold);

}

int GoalGetGold::process()
{
	return processSubgoals();
}

void GoalGetGold::terminate()
{
	_status = Goal::COMPLETE;
}
