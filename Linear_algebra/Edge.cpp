#include "Edge.h"
#include "Node.h"


Edge::Edge()
{
}

Edge::Edge(Node* source, Node* target, float travelCost) :
	_sourceNode(source),
	_targetNode(target),
	_travelCost(travelCost)
{}

Edge::~Edge()
= default;

const Node* Edge::getSource() const
{
	return _sourceNode;
}

const Node* Edge::getTarget() const
{
	return _targetNode;
}

void Edge::setTravelCost(float travelCost)
{
	_travelCost = travelCost;
}

const float Edge::getTravelCost() const
{
	return _travelCost;
}

void Edge::render(SDL_Renderer* gRenderer) const
{
	SDL_SetRenderDrawColor(
		gRenderer,
		0, 0, 0, 255);
	SDL_RenderDrawLine(
		gRenderer,
		_sourceNode->getPosition().x,
		_sourceNode->getPosition().y,
		_targetNode->getPosition().x,
		_targetNode->getPosition().y
	);
}
