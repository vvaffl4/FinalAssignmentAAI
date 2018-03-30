#ifndef ASTARGRAPHSEARCH_H
#define ASTARGRAPHSEARCH_H
#pragma once

#include "GraphSearch.h"
#include "TwoSidedEdge.h"
#include <queue>
#include <map>

class AStarGraphSearch : public GraphSearch
{
private:
	std::map<unsigned int, double>			_totalCostToNode;
	std::vector<const Edge*>	_shortedPathTree;	//Shortest current route
	std::vector<double>			_costToNode;		//Cost to node with index

public:
	AStarGraphSearch();
	~AStarGraphSearch();
	Path* searchGraph(const Node* start, const Node* end) override;
	bool operator()(const Node* i, const Node* j);
	bool visited(const std::vector<unsigned>& nodeVector, const unsigned int& index) const;
};

#endif