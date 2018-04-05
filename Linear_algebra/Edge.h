#ifndef EDGE_H
#define EDGE_H
#pragma once
#include <SDL_render.h>

class Node;

class Edge
{
protected:
	unsigned char _red		= 0;
	unsigned char _green	= 0;
	unsigned char _blue		= 0;
	unsigned char _alpha	= 255;

	Node* _sourceNode = nullptr;
	Node* _targetNode = nullptr;
	float _travelCost;

public:
	Edge();
	Edge(Node* source, Node* target, float travelCost);
	virtual ~Edge();
	const Node* getSource() const;
	const Node* getTarget() const;
	void render(SDL_Renderer* gRenderer) const;
	void setTravelCost(float travelCost);
	const float getTravelCost() const;
	void setColor(unsigned red, unsigned green, unsigned blue, unsigned alpha);
	virtual bool canTraverse(const Node* start) const = 0;
};

#endif