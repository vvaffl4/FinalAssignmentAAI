#ifndef GRAPHSEARCHHEURISTIC_H
#define GRAPHSEARCHHEURISTIC_H
#pragma once

#include "Vector2D.h"

class GraphSearchHeuristic
{
private:
	GraphSearchHeuristic();
public:
	static double calculateEuclid(const Vector2D& start, const Vector2D& end);
	static double calculateManhattan(const Vector2D& start, const Vector2D& end);
};

#endif