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

void Edge::setColor(unsigned red, unsigned green, unsigned blue, unsigned alpha)
{
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = alpha;
}

void Edge::render(SDL_Renderer* gRenderer) const
{
	SDL_SetRenderDrawColor(
		gRenderer,
		_red, _green, _blue, _alpha);
	SDL_RenderDrawLine(
		gRenderer,
		_sourceNode->getPosition().x,
		_sourceNode->getPosition().y,
		_targetNode->getPosition().x,
		_targetNode->getPosition().y
	);
}
