#include "Path.h"

Path::Path(bool repeat) :
	_repeat(repeat)
{
}

Path::~Path()
{
}

void Path::gotoNextWaypoint()
{
	if (++_currentWaypoint == _wayPoints.cend() && _repeat)
		_currentWaypoint = _wayPoints.cbegin();
}

void Path::addWaypoint(const Vector2D& waypoint)
{
	_wayPoints.push_back(waypoint);
}

const Vector2D& Path::getCurrentWaypoint() const
{
	return *_currentWaypoint;
}

void Path::begin()
{
	_currentWaypoint = _wayPoints.cbegin();
}

bool Path::finished() const
{
	return _currentWaypoint == _wayPoints.cend();
}

void Path::render(SDL_Renderer* gRenderer) const
{
	SDL_SetRenderDrawColor(
		gRenderer,
		255, 0, 0, 255);

	std::list<Vector2D>::const_iterator oldWaypoint;

	for (std::list<Vector2D>::const_iterator waypoint = _wayPoints.cbegin(); waypoint != _wayPoints.cend(); ++waypoint)
	{
		if(oldWaypoint._Ptr != nullptr)
		{
			SDL_RenderDrawLine(
				gRenderer,
				oldWaypoint->x,
				oldWaypoint->y,
				waypoint->x,
				waypoint->y
			);
		}

		oldWaypoint = waypoint;
	}
}
