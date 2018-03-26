#include "GraphSearchHeuristic.h"


GraphSearchHeuristic::GraphSearchHeuristic()
{
}

double GraphSearchHeuristic::calculateEuclid(const Vector2D& start, const Vector2D& end)
{
	return Vector2D::distance(start, end);
}

double GraphSearchHeuristic::calculateManhattan(const Vector2D& start, const Vector2D& end)
{
	return abs(end.x - start.x + end.y - start.y);
}
