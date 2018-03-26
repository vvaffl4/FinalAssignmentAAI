#ifndef ATTACK_H
#define ATTACK_H
#pragma once
#include "Guard.h"
#include "State.h"
#include "Hide.h"

class Attack : public State
{
public:
	Attack(StateMachine* stateMachine);
	~Attack();
	static Attack* instance(StateMachine* stateMachine);
	void enter(Guard* entity) override;
	void execute(Guard* entity) override;
	void exit(Guard* entity) override;
};

#endif