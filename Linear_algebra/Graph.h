#ifndef GRAPH_H
#define GRAPH_H
#pragma once

#include "Node.h"
#include "Path.h"
#include "GraphSearch.h"
#include <SDL_render.h>

class Graph
{
	std::vector<Node*> _nodeVector;
public:
	Graph();
	~Graph();
	Path* findPath(GraphSearch* graphSearch) const;
	void addNode(Node* node);
	void render(SDL_Renderer* gRenderer);
	void setNodes(std::vector<Node*>& nodeVector);
	inline Vector2D getNode(int index) { return _nodeVector[index]->getPosition(); }
};

#endif