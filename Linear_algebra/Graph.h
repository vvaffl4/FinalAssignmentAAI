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
	int _offsetX;
	int _offsetY;
	int _startX;
	int _startY;

	const Node* _findClosestNode(Vector2D point) const;
public:
	Graph();
	~Graph();
	Path* findPath(const Vector2D& start, const Vector2D& end, GraphSearch* graphSearch) const;
	void addNode(Node* node);
	void generateGraph();
	void floodfill(int x, int y, Node* previous);
	void render(SDL_Renderer* gRenderer) const;
	void setNodes(std::vector<Node*>& nodeVector);
	std::vector<Node*>& getNodes();
	const Vector2D& getNodePosition(int index);
};

#endif