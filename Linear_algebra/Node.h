#ifndef NODE_H
#define NODE_H
#pragma once
#include "Vector2D.h"
#include <vector>
#include "Edge.h"
#include <SDL.h>

class Node
{
private:
	unsigned int		_index;
	std::vector<Edge*>	_edgeVector;
	Vector2D			_position;
public:
	Node();
	Node(const Vector2D& position);
	~Node();
	void addEdge(Edge* edge);
	void setIndex(const unsigned int& index);
	const unsigned int& getIndex() const;
	const Vector2D& getPosition() const;
	const std::vector<Edge*> getEdges() const;
	void render(SDL_Renderer* gRenderer) const;
};

#endif