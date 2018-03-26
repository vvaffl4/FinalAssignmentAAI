#ifndef OBSTACLE_H
#define OBSTACLE_H
#pragma once
#include "BaseEntity.h"
#include <SDL.h>

class Obstacle : public BaseEntity
{
private:

public:
	Obstacle();
	~Obstacle();
	void render(SDL_Renderer* gRenderer);
};

#endif