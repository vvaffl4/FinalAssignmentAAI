#ifndef EDGE_H
#define EDGE_H
#pragma once
#include <SDL_render.h>

class Node;

class Edge
{
protected:
	Node* _sourceNode = nullptr;
	Node* _targetNode = nullptr;
	float _travelCost;

public:
	Edge();
	Edge(Node* source, Node* target, float travelCost);
	virtual ~Edge();
	const Node* getSource() const;
	const Node* getTarget() const;
	void setTravelCost(float travelCost);
	const float getTravelCost() const;
	virtual bool canTraverse(const Node* start) const = 0;
	void render(SDL_Renderer* gRenderer) const;
};

#endif