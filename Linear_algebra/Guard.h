#ifndef GUARD_H
#define GUARD_H
#pragma once
#include "MovingEntity.h"
#include "StateMachine.h"
#include "Patrol.h"

class Guard : public MovingEntity
{
private:
	StateMachine _stateMachine;

	int _strength = 10;
public:
	Guard();
	~Guard();
	void addStrength(int strength);
	void removeStrength(int strength);
	int getStrength() const;
	bool enemyIsClose() const;
	void update(double delta) override;
};

#endif