#ifndef PATH_H
#define PATH_H
#pragma once
#include <list>
#include "Vector2D.h"
#include "Edge.h"
#include <SDL.h>

class Path
{
private:
	bool _repeat = false;
	std::list<Vector2D>::const_iterator _currentWaypoint;
	std::list<Vector2D> _wayPoints;
public:
	Path(bool repeat);
	~Path();
	enum smoothingMethod{Rough, Precise};
	void gotoNextWaypoint();
	void addWaypoint(const Vector2D& waypoint);
	const Vector2D& getCurrentWaypoint() const;
	void begin();
	bool finished() const;
	void render(SDL_Renderer* gRenderer) const;
	Path* smoothPath(smoothingMethod method);
	void setRepeat(bool repeat);
};

#endif