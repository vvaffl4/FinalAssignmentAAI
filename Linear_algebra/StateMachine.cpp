#include "StateMachine.h"



StateMachine::StateMachine()
{
}


StateMachine::~StateMachine()
{
}

void StateMachine::setCurrentState(State* state)
{
	if(_currentState != nullptr)
		_currentState->exit(nullptr);

	_currentState = state;
	_currentState->enter(nullptr);
}

void StateMachine::changeCurrentState(State* state)
{
	_currentState = state;
}

void StateMachine::update(Guard* entity)
{
	if (_currentState != nullptr)
		_currentState->execute(entity);
}
