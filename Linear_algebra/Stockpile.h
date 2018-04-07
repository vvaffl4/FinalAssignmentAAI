#ifndef STOCKPILE_H
#define STOCKPILE_H
#pragma once
#include "BaseEntity.h"
#include "Deposit.h"

class Stockpile : public BaseEntity
{
protected:
	float _gold = 0;
	unsigned char _red = 0;
	unsigned char _green = 0;
	unsigned char _blue = 0;
	unsigned char _alpha = 255;

public:
	Stockpile();
	~Stockpile();
	void addGold(float gold);
	void render(SDL_Renderer* gRenderer);
};

#endif //STOCKPILE_H