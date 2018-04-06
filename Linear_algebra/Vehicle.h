#ifndef VEHICLE_H
#define VEHICLE_H
#pragma once

#include "Environment.h"
#include "Vector3D.h"
#include "MovingEntity.h"
#include "SteeringBehaviorGroup.h"
#include <SDL_render.h>

class SteeringBehaviorGroup;

class Vehicle : public MovingEntity
{
private:
	unsigned char _red = 0;
	unsigned char _green = 0;
	unsigned char _blue = 0;
	unsigned char _alpha = 255;

	Vector2D _topMiddle;// = Vector2D(0, -10);
	Vector2D _bottomLeft;// = Vector2D(-5, 10);
	Vector2D _bottomRight;// = Vector2D(5, 10);

	Environment* _environment;
	SteeringBehaviorGroup* _steeringBehavior;

public:
	Vehicle();
	Vehicle(Environment* environment, SDL_Renderer* renderer);
	~Vehicle();
	virtual void update(double delta);
	void render(SDL_Renderer* gRenderer);
	void setColor(unsigned red, unsigned green, unsigned blue, unsigned alpha);
	SteeringBehaviorGroup* getSteering() const;
	Environment* getEnvironment() const;
};

#endif