#include "Graph.h"
#include <SDL.h>
#include "Environment.h"
#include "TwoSidedEdge.h"


Graph::Graph()
{
}


Graph::~Graph()
{
}

Path* Graph::findPath(GraphSearch* graphSearch) const
{
	return graphSearch->searchGraph();
}

void Graph::addNode(Node* node)
{
	_nodeVector.push_back(node);
}

void Graph::generateGraph()
{
	_startX = 400;
	_startY = 210;

	_offsetX = 45;
	_offsetY = 45;

	floodfill(0, 0, nullptr);
}

void Graph::floodfill(int x, int y, Node* previous)
{
	if (x > 10 || x < -10 || y > 10 || y < -10)
		return;

	Environment* environment = Environment::GetInstance();

	if(previous != nullptr)
	{ 
		if (environment->isPathObstructed(
			previous->getPosition(), 
			Vector2D(
				_startX + (x * _offsetX), 
				_startY + (y * _offsetY))) ||
			environment->isEdgeObstructed(
				previous->getPosition(),
				Vector2D(
					_startX + (x * _offsetX),
					_startY + (y * _offsetY))))
			return;
	}

	for(auto nodeIt = _nodeVector.begin(); nodeIt != _nodeVector.end(); ++nodeIt)
	{
		Node* node = (*nodeIt);

		if(node->getPosition().x == _startX + (x * _offsetX)  &&
			node->getPosition().y == _startY + (y * _offsetY))
		{
			Edge* edgeForth = new TwoSidedEdge(node, previous, 1.0f);
			Edge* edgeBack = new TwoSidedEdge(previous, node, 1.0f);

			if (!previous->addEdge(edgeBack))
				delete edgeBack;

			if(!node->addEdge(edgeForth))
				delete edgeForth;

			return;
		}
	}

	Node* node = new Node(Vector2D(
		_startX + x * _offsetX, 
		_startY + y * _offsetY));
	node->setIndex(_nodeVector.size());
	_nodeVector.push_back(node);

	floodfill(x, y + 1, node);
	floodfill(x, y - 1, node);
	floodfill(x + 1, y, node);
	floodfill(x - 1, y, node);
}

void Graph::render(SDL_Renderer* gRenderer)
{
	for(auto node = _nodeVector.cbegin(); node != _nodeVector.cend(); ++node)
		(*node)->render(gRenderer);
}

void Graph::setNodes(std::vector<Node*>& nodeVector)
{
	_nodeVector = nodeVector;
}

std::vector<Node*>& Graph::getNodes()
{
	return _nodeVector;
}