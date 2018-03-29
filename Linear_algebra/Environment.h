#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#pragma once

#include <vector>
#include "Obstacle.h"
#include "Wall.h"
#include <vector>

class Vehicle;

class Environment
{
private:

	static Environment* environment;
	std::vector<Obstacle*>	_obstacles;
	std::vector<Wall*>		_walls;
	std::vector<Vehicle*>	_vehicles;
	
	Environment();

public:
	static Environment* GetInstance();
	~Environment();
	void addVehicle(Vehicle* vehicle);
	const std::vector<Vehicle*>& getVehicles() const;
	void addObstacle(Obstacle* obstacle);
	const std::vector<Obstacle*>& getObstacles() const;
	void addWall(Wall* wall);
	const std::vector<Wall*>& getWalls() const;

	bool rayIntersectsObstacle(Vector2D start, Vector2D end, Obstacle* obs);
	bool isPathObstructed(Vector2D start, Vector2D end);
};


#endif