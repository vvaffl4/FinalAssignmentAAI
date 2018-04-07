#ifndef DEPOSIT_H
#define DEPOSIT_H

#pragma once
#include "BaseEntity.h"
#include "Edge.h"

class Deposit : public BaseEntity
{
private:
	float _gold;

public:
	Deposit(int gold);
	~Deposit();
	float take(float amount);
	bool empty() const;
	void render(SDL_Renderer* gRenderer);
};

#endif //DEPOSIT_H