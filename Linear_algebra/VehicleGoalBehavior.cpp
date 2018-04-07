#include "VehicleGoalBehavior.h"



VehicleGoalBehavior::VehicleGoalBehavior()
{
}

VehicleGoalBehavior::VehicleGoalBehavior(Environment* environment, SDL_Renderer* gRenderer) :
	Vehicle(environment, gRenderer),
	_behavior(new GoalThink(this))
{
	_behavior->activate();
}


VehicleGoalBehavior::~VehicleGoalBehavior()
{
	_behavior->terminate();
	delete _behavior;
}

void VehicleGoalBehavior::update(double delta)
{
	_behavior->process();

	Vehicle::update(delta);
}

void VehicleGoalBehavior::addGold(float gold)
{
	_gold += gold;
	_food -= 0.01f;

	std::cout << "Vehicle gold: " << _gold << std::endl;
}

float VehicleGoalBehavior::takeGold(float amount)
{
	_gold -= amount;
	_food -= 0.01f;

	if (_gold < 0)
	{
		const float overflow = _gold;
		_gold = 0;
		return overflow + amount;
	}

	std::cout << "Vehicle gold: " << _gold << std::endl;

	return amount;
}

bool VehicleGoalBehavior::isFull() const
{
	return _gold >= 80;
}

bool VehicleGoalBehavior::empty()
{
	return _gold <= 0;
}

float VehicleGoalBehavior::getTransferRate() const
{
	return _transferRate;
}

void VehicleGoalBehavior::addFood(float food)
{
	_food += food;

	std::cout << "Vehicle food: " << _food << std::endl;
}

bool VehicleGoalBehavior::isFoodFull() const
{
	return _food >= 20;
}

bool VehicleGoalBehavior::isFoodLow() const
{
	return _food <= 5;
}

void VehicleGoalBehavior::takeFood(float food)
{
	_food -= food;

	if (_food < 0)
		_food = 0;
}
