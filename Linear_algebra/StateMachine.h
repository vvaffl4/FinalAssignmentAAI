#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#pragma once

#include "State.h"

class Guard;

class StateMachine
{
private:
	State* _currentState = nullptr;
public:
	StateMachine();
	~StateMachine();
	void setCurrentState(State* state);
	void changeCurrentState(State* state);
	void update(Guard* entity);
};

#endif