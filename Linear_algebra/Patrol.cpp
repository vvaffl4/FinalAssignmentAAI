#include "Patrol.h"
#include "StateMachine.h"


Patrol::Patrol(StateMachine* stateMachine) :
	State(stateMachine)
{
}


Patrol::~Patrol()
{
}

void Patrol::enter(Guard* entity)
{
	std::cout << "Guard start patrolling" << std::endl;
}

void Patrol::execute(Guard* entity)
{
	entity->addStrength(1);
	if (entity->getStrength() <= 10 && entity->enemyIsClose())
		_stateMachine->setCurrentState(Hide::instance(_stateMachine));
	if (entity->getStrength() > 10 && entity->enemyIsClose())
		_stateMachine->setCurrentState(Attack::instance(_stateMachine));
}

void Patrol::exit(Guard* entity)
{
	std::cout << "Guard stop patrolling" << std::endl;
}

Patrol* Patrol::instance(StateMachine* stateMachine)
{
	return new Patrol(stateMachine);
}
