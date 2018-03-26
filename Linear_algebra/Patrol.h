#ifndef PATROL_H
#define PATROL_H
#pragma once

#include "Guard.h"
#include "State.h"
#include "StateMachine.h"
#include "Hide.h"
#include "Attack.h"
#include <iostream>

class Patrol : public State
{

public:
	Patrol(StateMachine* stateMachine);
	~Patrol();
	void enter(Guard* entity) override;
	void execute(Guard* entity) override;
	void exit(Guard* entity) override;
	static Patrol* instance(StateMachine* stateMachine);
};

#endif