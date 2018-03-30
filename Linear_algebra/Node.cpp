#include "Node.h"



Node::Node()
{
}

Node::~Node()
= default;

Node::Node(const Vector2D& position) :
	_position(position)
{}

bool Node::addEdge(Edge* edge)
{
	for(auto edgeIt = _edgeVector.cbegin(); edgeIt != _edgeVector.cend(); ++edgeIt)
	{
		if (edge->getSource()->getIndex() == (*edgeIt)->getSource()->getIndex() &&
			edge->getTarget()->getIndex() == (*edgeIt)->getTarget()->getIndex())
			return false;
	}

	_edgeVector.push_back(edge);
	return true;
}

void Node::setIndex(const unsigned int & index)
{
	_index = index;
}

const unsigned int& Node::getIndex() const
{
	return _index;
}

const Vector2D& Node::getPosition() const
{
	return _position;
}

const std::vector<Edge*> Node::getEdges() const
{
	return _edgeVector;
}

void Node::render(SDL_Renderer* gRenderer) const
{
	for (auto edge = _edgeVector.cbegin(); edge != _edgeVector.cend(); ++edge)
		(*edge)->render(gRenderer);

	float quarterPI = 3.14159 * 0.25;

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	for (int i = 0; i < 8; ++i)
	{
		SDL_RenderDrawLine(
			gRenderer,
			_position.x + 5 * sin(quarterPI * i),
			_position.y + 5 * cos(quarterPI * i),
			_position.x + 5 * sin(quarterPI * (i + 1)),
			_position.y + 5 * cos(quarterPI * (i + 1)));
	}
}
