#ifndef TWOSIDEDEDGE_H
#define TWOSIDEDEDGE_H
#pragma once

#include "Edge.h"

class TwoSidedEdge : public Edge
{
public:
	TwoSidedEdge();
	TwoSidedEdge(Node* source, Node* target, float travelCost);
	~TwoSidedEdge();
	bool canTraverse(const Node* start) const override;
};

#endif