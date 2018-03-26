#include "TwoSidedEdge.h"

TwoSidedEdge::TwoSidedEdge()
= default;

TwoSidedEdge::TwoSidedEdge(Node* source, Node* target, const float travelCost) :
	Edge(source, target, travelCost)
{}


TwoSidedEdge::~TwoSidedEdge()
= default;

bool TwoSidedEdge::canTraverse(const Node* start) const
{
	return true;
}
