#include "Graph.h"
#include <SDL.h>


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

void Graph::render(SDL_Renderer* gRenderer)
{
	for(auto node = _nodeVector.cbegin(); node != _nodeVector.cend(); ++node)
		(*node)->render(gRenderer);
}

void Graph::setNodes(std::vector<Node*>& nodeVector)
{
	_nodeVector = nodeVector;
}
