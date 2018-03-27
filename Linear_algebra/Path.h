#ifndef PATH_H
#define PATH_H
#pragma once
#include <list>
#include "Vector2D.h"
#include "Edge.h"

class Path
{
private:
	bool _repeat = false;
	std::list<Vector2D>::const_iterator _currentWaypoint;
	std::list<Vector2D> _wayPoints;
	enum smoothingMethod{Rough, Precise};
public:
	Path(bool repeat);
	~Path();
	void gotoNextWaypoint();
	void addWaypoint(const Vector2D& waypoint);
	const Vector2D& getCurrentWaypoint() const;
	void begin();
	bool finished() const;
	void render(SDL_Renderer* gRenderer) const;
	void smoothPath(smoothingMethod method);
};

#endif