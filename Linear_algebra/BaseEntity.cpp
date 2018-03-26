#include "BaseEntity.h"


BaseEntity::BaseEntity() :
	_position(Vector2D(0.0f, 0.0f)),
	_scale(Vector2D(1.0f, 1.0f))
{}


BaseEntity::~BaseEntity()
{
}

void BaseEntity::setPosition(const Vector2D& position)
{
	_position = position;
}

const Vector2D& BaseEntity::getPosition() const
{
	return _position;
}

void BaseEntity::setScale(const Vector2D& scale)
{
	_scale = scale;
}

const Vector2D& BaseEntity::getScale() const
{
	return _scale;
}

void BaseEntity::setBoundingRadius(float boundingRadius)
{
	_boundingRadius = boundingRadius;
}

float BaseEntity::getBoundingRadius() const
{
	return _boundingRadius;
}

float BaseEntity::getRadius() const
{
	return _boundingRadius;
}

unsigned BaseEntity::getId() const
{
	return _id;
}
