#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#pragma once

#include <vector>
#include "Obstacle.h"
#include "Wall.h"
#include "Graph.h"

class Vehicle;

class Environment
{
private:

	int						_width = 0;
	int						_height = 0;

	static Environment*		_environment;
	std::vector<Obstacle*>	_obstacles;
	std::vector<Wall*>		_walls;
	std::vector<Vehicle*>	_vehicles;
	Graph*					_graph;
	
	bool _graphRender = false;

	Environment();

public:
	static Environment* GetInstance();
	~Environment();
	void generateGraph();
	Path* findPath(const Vector2D& start, const Vector2D& end) const;
	void render(SDL_Renderer* gRenderer, double delta);
	bool rayIntersectsObstacle(Vector2D start, Vector2D end, Obstacle* obs);
	bool isPathObstructed(Vector2D start, Vector2D end);
	bool isEdgeObstructed(const Vector2D& start, const Vector2D& end);
	bool isPointOutside(const Vector2D& point) const;
	void setSize(int width, int height);
	void addVehicle(Vehicle* vehicle);
	const std::vector<Vehicle*>& getVehicles() const;
	void addObstacle(Obstacle* obstacle);
	const std::vector<Obstacle*>& getObstacles() const;
	void addWall(Wall* wall);
	const std::vector<Wall*>& getWalls() const;
	void toggleGraphRendering();
	const Graph* getGraph() const;
};


#endif