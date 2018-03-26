#ifndef HIDE_H
#define HIDE_H
#pragma once
#include "Guard.h"
#include "StateMachine.h"
#include "State.h"
#include "Patrol.h"
#include <iostream>

class Hide : public State
{
public:
	Hide(StateMachine* stateMachine);
	~Hide();
	static Hide* instance(StateMachine* stateMachine);
	void enter(Guard* entity) override;
	void execute(Guard* entity) override;
	void exit(Guard* entity) override;
};

#endif