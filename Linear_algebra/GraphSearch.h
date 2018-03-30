#ifndef GRAPHSEARCH_H
#define GRAPHSEARCH_H
#pragma once
#include "Path.h"
#include "Node.h"

class GraphSearch
{
protected:
	Node* _start;
	Node* _end;
public:
	GraphSearch();
	virtual ~GraphSearch();
	virtual Path* searchGraph(const Node* start, const Node* end) = 0;
};

#endif