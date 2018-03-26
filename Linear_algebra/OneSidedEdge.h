#ifndef ONESIDEDEDGE_H
#define ONESIDEDEDGE_H
#pragma once

#include "Edge.h"

class OneSidedEdge : public Edge
{
public:
	OneSidedEdge();
	OneSidedEdge(Node* from, Node* to, float travelCost);
	~OneSidedEdge();
	bool canTraverse(const Node* start) const override;
};

#endif