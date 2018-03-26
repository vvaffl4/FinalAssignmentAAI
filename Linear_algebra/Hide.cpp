#include "Hide.h"

Hide::Hide(StateMachine* stateMachine) :
	State(stateMachine)
{}


Hide::~Hide()
{
}

Hide* Hide::instance(StateMachine* stateMachine)
{
	return new Hide(stateMachine);
}

void Hide::enter(Guard* entity)
{
	std::cout << "Guard start hiding" << std::endl;
}

void Hide::execute(Guard* entity)
{
	entity->addStrength(1);
	if (!entity->enemyIsClose())
		_stateMachine->setCurrentState(Patrol::instance(_stateMachine));
}

void Hide::exit(Guard* entity)
{
	std::cout << "Guard stop hiding" << std::endl;
}
