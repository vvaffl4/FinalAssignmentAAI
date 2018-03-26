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
	GraphSearch(Node* start, Node* end);
	virtual ~GraphSearch();
	virtual Path* searchGraph() = 0;
};

#endif