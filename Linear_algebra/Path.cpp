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

void Path::smoothPath(smoothingMethod method) {
	//start at first node
	Vector2D curr = _wayPoints.front();
	int current = 0;

	//switch for smoothing method
	switch (method) {
	case Rough:
		//while path from current to 'next' is unobstructed
		//loop from current to end of the list
		//update 'next'

		//repeat until current is end of the list

		for (std::list<Vector2D>::iterator iter = std::next(_wayPoints.begin(), current); iter != _wayPoints.end(); ++iter){
			//if path from curr to iter is unobstructed, proceed
			//else, path[curr + 1] = previous
		}
	case Precise:
		//start loop at end of list
		//loop backwards until an unobstructed path is found
		//update current
		
		//repeat until current is last
	}
}
