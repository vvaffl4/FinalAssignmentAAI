#include "GoalGetFood.h"
#include "GoalGetGold.h"
#include "Environment.h"
#include "GoalArrive.h"
#include "GoalStockpileGold.h"
#include "VehicleGoalBehavior.h"
#include "GoalTakeFood.h"


GoalGetFood::GoalGetFood(VehicleGoalBehavior* vehicle) :
	CompositeGoal(vehicle)
{}


GoalGetFood::~GoalGetFood()
= default;

void GoalGetFood::activate()
{
	Food* food = Environment::GetInstance()->getClosestAvailableFood(_vehicle->getPosition());

	GoalArrive* goalArriveFood = new GoalArrive(_vehicle);
	goalArriveFood->setDestination(food->getPosition());
	goalArriveFood->activate();
	_goalList.push_back(goalArriveFood);

	GoalTakeFood* goalTakeFood = new GoalTakeFood(_vehicle);
	goalTakeFood->setFood(food);
	_goalList.push_back(goalTakeFood);
}

int GoalGetFood::process()
{
	return processSubgoals();
}

void GoalGetFood::terminate()
{
	_status = Goal::COMPLETE;
}
