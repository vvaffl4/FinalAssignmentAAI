#include "Environment.h"



Environment::Environment()
{
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
