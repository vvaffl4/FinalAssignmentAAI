#ifndef FOOD_H
#define FOOD_H

#pragma once
#include "BaseEntity.h"
#include "Edge.h"

class Food : public BaseEntity
{
private:

public:
	Food();
	~Food();
	float take(float amount) const;
	void render(SDL_Renderer* gRenderer) const;
};

#endif //FOOD_H