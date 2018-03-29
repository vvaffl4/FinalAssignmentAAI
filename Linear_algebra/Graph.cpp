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
	Environment* environment = Environment::GetInstance();

	_startX = 400;
	_startY = 300;

	_offsetX = 30;
	_offsetY = 30;

	floodfill(0, 0, nullptr);
}

void Graph::floodfill(int x, int y, Node* previous)
{
	for(auto nodeIt = _nodeVector.begin(); nodeIt != _nodeVector.end(); ++nodeIt)
	{
		Node* node = (*nodeIt);

		if(node->getPosition().x == _startX + (x * _offsetX)  &&
			node->getPosition().y == _startY + (y * _offsetY))
		{
			Edge* edgeForth = new TwoSidedEdge(node, previous, 1.0f);
			Edge* edgeBack = new TwoSidedEdge(previous, node, 1.0f);

			previous->addEdge(edgeBack);
			node->addEdge(edgeForth);

			return;
		}
	}

	Node* node = new Node(Vector2D(
		_startX + x * _offsetX, 
		_startY + y * _offsetY));
	node->setIndex(_nodeVector.size());
	_nodeVector.push_back(node);

	if(previous != nullptr)
	{
		Edge* edgeForth = new TwoSidedEdge(node, previous, 1.0f);
		Edge* edgeBack = new TwoSidedEdge(previous, node, 1.0f);

		node->addEdge(edgeForth);
		previous->addEdge(edgeBack);
	}

	if (x > 3 || x < -3 || y > 3 || y < -3)
		return;

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