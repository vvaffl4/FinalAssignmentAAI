#include "Path.h"
#include "Environment.h"

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

Path* Path::smoothPath(smoothingMethod method)
{
	//start at first node
	Vector2D curr = _wayPoints.front();
	int current = 0;
	Environment* env = Environment::GetInstance();

	Path* newPath = new Path(false);
	newPath->addWaypoint(curr);

	//switch for smoothing method
	Vector2D prev;
	switch (method) 
	{
	case Rough:
		//start at current
		//step forward until path is obstructed
		//previously visited node comes after current
		//update current
		//repeat until we reach the last node
		prev = _wayPoints.front();
		while (curr != _wayPoints.back()) {
			for (std::list<Vector2D>::iterator iter = std::next(_wayPoints.begin(), current); iter != _wayPoints.end(); ++iter) {
				if (env->isPathObstructed(curr, (*iter))) {
					//if path to current node is obstructed, we can't update the path to here
					break;
				}
				//keep track of previously visited node
				prev = (*iter);
				current++;
			}
			//update new path to include previously visited point
			newPath->addWaypoint(prev);
			curr = prev;
		}

	case Precise:
		//start loop at end of list
		//loop backwards until an unobstructed path is found
		//update current
		
		//repeat until current is last
		prev = _wayPoints.back();
		while (curr != _wayPoints.back()) {
			for (std::list<Vector2D>::reverse_iterator iter = _wayPoints.rbegin(); (*iter) != curr; ++iter) {
				if (env->isPathObstructed(curr, (*iter)))
				{
					//continue
				}
				else
				{
					//add prev to newPath
					newPath->addWaypoint(prev);
					curr = prev;
					break;
				}
				prev = (*iter);
				current++;
			}
		}
	}

	return newPath;
}
