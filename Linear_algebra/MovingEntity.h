#ifndef MOVING_ENTITY_H
#define MOVING_ENTITY_H
#pragma once

#include "BaseEntity.h"
#include "Vector2D.h"

class MovingEntity : public BaseEntity
{
protected:
	Vector2D _velocity;
	Vector2D _heading;
	Vector2D _side;

	double _mass = 1;
	double _maxSpeed = 25;
	double _maxForce;
	double _maxTurnRate;

public:
	MovingEntity();
	~MovingEntity();
	void update(double delta);
	void render();
	Vector2D getVelocity() const;
	const Vector2D& getHeading() const;
	const Vector2D& getSide() const;
	double getMass() const;
	void setMaximumSpeed(double speed);
	double getMaximumSpeed() const;
	void setMaximumForce(double maxForce);
	double getMaximumForce();
	double getMaximumTurnRate();
};

#endif