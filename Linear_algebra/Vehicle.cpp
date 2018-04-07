#include "Vehicle.h"
#include <SDL.h>


Vehicle::Vehicle() :
	_steeringBehavior(new SteeringBehaviorGroup(this, nullptr))
{
	_topMiddle = Vector2D(0, -10);
	_bottomLeft = Vector2D(-5, 10);
	_bottomRight = Vector2D(5, 10);

	_red = 0;
	_green = 0;
	_blue = 0;
	_alpha = 255;
}

Vehicle::Vehicle(Environment* environment, SDL_Renderer* renderer) :
	_environment(environment),
	_steeringBehavior(new SteeringBehaviorGroup(this, renderer))
{
	_topMiddle = Vector2D(0, -10);
	_bottomLeft = Vector2D(-5, 10);
	_bottomRight = Vector2D(5, 10);

	_red = 0;
	_green = 0;
	_blue = 0;
	_alpha = 255;
}


Vehicle::~Vehicle()
{
	delete _steeringBehavior;
}

void Vehicle::update(double delta)
{
	Vector2D steeringForce = _steeringBehavior->calculateWTRSwP();

	if (steeringForce.magnitude() == 0.0f)
		return;

	Vector2D acceleration = steeringForce / _mass;

	_velocity += acceleration * delta;
	_velocity.clamp(static_cast<float>(_maxSpeed));

	_position += _velocity * delta;

	if(_velocity.magnitudeSqrt() > 0.00001)
	{
		_heading = Vector2D::normalize(_velocity);
		_side = Vector2D::perpendicular(_heading);
	}

	//Possible wrap around the screen.
	if (_position.x < 0)
		_position.x = 800;
	if (_position.x > 800)
		_position.x = 0;
	if (_position.y < 0)
		_position.y = 600;
	if (_position.y > 600)
		_position.y = 0;
}

void Vehicle::render(SDL_Renderer* gRenderer)
{
	Matrix positionMatrix = Matrix(3, 3)
		.scale(_scale)
		.rotate(_side.toRadians())
		.translate(_position);

	Vector2D vector1 = positionMatrix * _topMiddle;
	Vector2D vector2 = positionMatrix * _bottomLeft;
	Vector2D vector3 = positionMatrix * _bottomRight;

	SDL_SetRenderDrawColor(gRenderer, 
		_red, _green, _blue, _alpha);
	SDL_RenderDrawLine(
		gRenderer,
		static_cast<int>(vector1.x),
		static_cast<int>(vector1.y),
		static_cast<int>(vector2.x),
		static_cast<int>(vector2.y));
	SDL_RenderDrawLine(
		gRenderer,
		static_cast<int>(vector2.x), 
		static_cast<int>(vector2.y), 
		static_cast<int>(vector3.x), 
		static_cast<int>(vector3.y));
	SDL_RenderDrawLine(
		gRenderer,
		static_cast<int>(vector3.x), 
		static_cast<int>(vector3.y), 
		static_cast<int>(vector1.x), 
		static_cast<int>(vector1.y));
}

SteeringBehaviorGroup* Vehicle::getSteering() const
{
	return _steeringBehavior;
}

Environment* Vehicle::getEnvironment() const
{
	return _environment;
}
