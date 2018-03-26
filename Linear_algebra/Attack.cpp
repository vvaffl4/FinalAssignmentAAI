#include "Attack.h"

Attack::Attack(StateMachine* stateMachine) :
	State(stateMachine)
{}


Attack::~Attack()
{
}

Attack* Attack::instance(StateMachine* stateMachine)
{
	return new Attack(stateMachine);
}

void Attack::enter(Guard* entity)
{
	std::cout << "Guard start attacking" << std::endl;
}

void Attack::execute(Guard* entity)
{
	entity->removeStrength(1);
	if (entity->getStrength() < 5)
		_stateMachine->setCurrentState(Hide::instance(_stateMachine));
}

void Attack::exit(Guard* entity)
{
	std::cout << "Guard stop attacking" << std::endl;
}
