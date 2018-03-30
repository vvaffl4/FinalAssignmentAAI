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


const Node* Graph::_findClosestNode(Vector2D point) const
{
	Node* closestNode = nullptr;
	double closestNodeDistance = DBL_MAX;

	for(auto nodeIt = _nodeVector.cbegin(); nodeIt != _nodeVector.cend(); ++nodeIt)
	{
		double distance = Vector2D::distance((*nodeIt)->getPosition(), point);

		if(closestNodeDistance > distance)
		{
			closestNodeDistance = distance;
			closestNode = (*nodeIt);
		}
	}

	return closestNode;
}

Path* Graph::findPath(const Vector2D& start, const Vector2D& end, GraphSearch* graphSearch) const
{
	const Node* startNode = _findClosestNode(start);
	const Node* endNode = _findClosestNode(end);

	return graphSearch->searchGraph(startNode, endNode);
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
	Environment* environment = Environment::GetInstance();

	if(previous != nullptr)
	{
		if (environment->isEdgeObstructed(
			previous->getPosition(),
			Vector2D(
				static_cast<float>(_startX + (x * _offsetX)),
				static_cast<float>(_startY + (y * _offsetY)))))
		{
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
	}

	Node* node = new Node(Vector2D(
		static_cast<float>(_startX + x * _offsetX),
		static_cast<float>(_startY + y * _offsetY)));
	node->setIndex(_nodeVector.size());
	_nodeVector.push_back(node);

	floodfill(x, y + 1, node);
	floodfill(x, y - 1, node);
	floodfill(x + 1, y, node);
	floodfill(x - 1, y, node);
}

void Graph::render(SDL_Renderer* gRenderer) const
{
	for (auto node : _nodeVector)
		node->render(gRenderer);
}

void Graph::setNodes(std::vector<Node*>& nodeVector)
{
	_nodeVector = nodeVector;
}

std::vector<Node*>& Graph::getNodes()
{
	return _nodeVector;
}

const Vector2D& Graph::getNodePosition(int index)
{
	return _nodeVector[index]->getPosition();
}
