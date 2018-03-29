#include "Environment.h"



Environment::Environment()
{
}


Environment* Environment::environment = 0;
Environment* Environment::GetInstance() {
	if (environment == 0)
		environment = new Environment();
	return environment;
}


Environment::~Environment()
{
}

void Environment::addVehicle(Vehicle* vehicle)
{
	_vehicles.push_back(vehicle);
}

const std::vector<Vehicle*>& Environment::getVehicles() const
{
	return _vehicles;
}

void Environment::addObstacle(Obstacle* obstacle)
{
	_obstacles.push_back(obstacle);
}

const std::vector<Obstacle*>& Environment::getObstacles() const
{
	return _obstacles;
}

void Environment::addWall(Wall* wall)
{
	_walls.push_back(wall);
}

const std::vector<Wall*>& Environment::getWalls() const
{
	return _walls;
}

bool Environment::rayIntersectsObstacle(Vector2D start, Vector2D end, Obstacle* obs)
{
	Vector2D d = end - start;
	Vector2D f = start - obs->getPosition();
	float r = obs->getRadius();

	float a = d.dotProduct(d);
	float b = 2 * f.dotProduct(d);
	float c = f.dotProduct(f) - r * r;

	float discriminant = b * b - 4 * a*c;
	if (discriminant < 0)
	{
		// no intersection
		return false;
	}
	else
	{
		// ray didn't totally miss sphere,
		// so there is a solution to
		// the equation.

		discriminant = sqrt(discriminant);

		// either solution may be on or off the ray so need to test both
		// t1 is always the smaller value, because BOTH discriminant and
		// a are nonnegative.
		float t1 = (-b - discriminant) / (2 * a);
		float t2 = (-b + discriminant) / (2 * a);

		// 3x HIT cases:
		//          -o->             --|-->  |            |  --|->
		// Impale(t1 hit,t2 hit), Poke(t1 hit,t2>1), ExitWound(t1<0, t2 hit), 

		// 3x MISS cases:
		//       ->  o                     o ->              | -> |
		// FallShort (t1>1,t2>1), Past (t1<0,t2<0), CompletelyInside(t1<0, t2>1)

		if (t1 >= 0 && t1 <= 1)
		{
			// t1 is the intersection, and it's closer than t2
			// (since t1 uses -b - discriminant)
			// Impale, Poke
			return true;
		}

		// here t1 didn't intersect so we are either started
		// inside the sphere or completely past it
		if (t2 >= 0 && t2 <= 1)
		{
			// ExitWound
			return true;
		}

		// no intn: FallShort, Past, CompletelyInside
		return false;
	}
}

bool Environment::isPathObstructed(Vector2D start, Vector2D end)
{
	for (auto iter = getObstacles().cbegin(); iter != getObstacles().cend(); iter++) {
		if (rayIntersectsObstacle(start, end, (*iter)))
			return true;
	}
	return false;
}
