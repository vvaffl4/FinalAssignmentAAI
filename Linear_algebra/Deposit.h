#ifndef DEPOSIT_H
#define DEPOSIT_H

#pragma once
#include "BaseEntity.h"
#include "Edge.h"

class Deposit : public BaseEntity
{
private:
	unsigned char _red = 0;
	unsigned char _green = 0;
	unsigned char _blue = 0;
	unsigned char _alpha = 255;

	float _gold;

public:
	Deposit(int gold);
	~Deposit();
	float take(float amount);
	bool empty() const;
	void render(SDL_Renderer* gRenderer);
	void setColor(unsigned red, unsigned green, unsigned blue, unsigned alpha);
};

#endif //DEPOSIT_H