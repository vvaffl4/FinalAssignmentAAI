#include "MovingEntity.h"



MovingEntity::MovingEntity() :
	_velocity(Vector2D(0.0f, 0.0f)),
	_heading(Vector2D(0.0f, -1.0f))
{
}


MovingEntity::~MovingEntity()
{
}

Vector2D MovingEntity::getVelocity() const
{
	return _velocity;
}

const Vector2D& MovingEntity::getHeading() const
{
	return _heading;
}

const Vector2D& MovingEntity::getSide() const
{
	return _side;
}

double MovingEntity::getMass() const
{
	return _mass;
}

void MovingEntity::setMaximumSpeed(double speed)
{
	_maxSpeed = speed;
}

double MovingEntity::getMaximumSpeed() const
{
	return _maxSpeed;
}

void MovingEntity::setMaximumForce(double maxForce)
{
	_maxForce = maxForce;
}

double MovingEntity::getMaximumForce()
{
	return _maxForce;
}

double MovingEntity::getMaximumTurnRate()
{
	return _maxTurnRate;
}
