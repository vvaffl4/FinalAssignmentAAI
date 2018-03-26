#ifndef STATE_H
#define STATE_H
#pragma once

class Guard;
class StateMachine;

class State
{
protected:
	StateMachine* _stateMachine = nullptr;

public:
	State(StateMachine* stateMachine);
	virtual ~State();
	virtual void enter(Guard* entity) = 0;
	virtual void execute(Guard* entity) = 0;
	virtual void exit(Guard* entity) = 0;
};

#endif