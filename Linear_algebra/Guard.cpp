#include "Guard.h"

Guard::Guard()
{
	_stateMachine = StateMachine();
	_stateMachine.setCurrentState(Patrol::instance(&_stateMachine));
}


Guard::~Guard()
{
}

void Guard::addStrength(int strength)
{
	_strength += strength;
}

void Guard::removeStrength(int strength)
{
	_strength -= strength;
}

int Guard::getStrength() const
{
	return _strength;
}

bool Guard::enemyIsClose() const
{
	return true;
}

void Guard::update(double delta)
{
	_stateMachine.update(this);
}