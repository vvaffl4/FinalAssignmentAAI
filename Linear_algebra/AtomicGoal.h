#ifndef ATOMICGOAL_H
#define ATOMICGOAL_H
#pragma once

#include "Goal.h"

class AtomicGoal : public Goal
{
public:
	AtomicGoal(Vehicle* vehicle);
	~AtomicGoal();
};

#endif //ATOMICGOAL_H