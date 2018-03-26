#include "OneSidedEdge.h"



OneSidedEdge::OneSidedEdge()
= default;

OneSidedEdge::OneSidedEdge(Node* from, Node* to, const float travelCost) :
	Edge(from, to, travelCost)
{}


OneSidedEdge::~OneSidedEdge()
= default;

bool OneSidedEdge::canTraverse(const Node* start) const
{
	return start == _sourceNode;
}
