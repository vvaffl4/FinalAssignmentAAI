#ifndef DEPTHFIRSTGRAPHSEARCH_H
#define DEPTHFIRSTGRAPHSEARCH_H
#pragma once

#include "GraphSearch.h"
#include <stack>
#include <map>

class DepthFirstGraphSearch : public GraphSearch
{
public:
	DepthFirstGraphSearch();
	~DepthFirstGraphSearch();
	Path* searchGraph(const Node* start, const Node* end) override;
	bool visited(const std::vector<unsigned>& nodeVector, const unsigned& index) const;
	const Node* _target;
};

#endif