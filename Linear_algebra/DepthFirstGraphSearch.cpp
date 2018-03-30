#include "DepthFirstGraphSearch.h"
#include "TwoSidedEdge.h"


DepthFirstGraphSearch::DepthFirstGraphSearch()
{
}

DepthFirstGraphSearch::~DepthFirstGraphSearch()
{
}

Path* DepthFirstGraphSearch::searchGraph(const Node* start, const Node* end)
{
	Path* path = new Path(false);

	//Stack of edges
	std::stack<const Edge*> edgeStack;
	std::vector<unsigned int> nodesVisitedMap;

	//Starting node
	TwoSidedEdge dummy(_start, _start, 0);

	edgeStack.push(&dummy);

	while(!edgeStack.empty())
	{
		const Edge* currentEdge = edgeStack.top();
		const Node* currentNode = currentEdge->getTarget();
		const std::vector<Edge*> nextEdgeVector = currentEdge->getTarget()->getEdges();
		
		edgeStack.pop();

		path->addWaypoint(currentEdge->getSource()->getPosition());
		
		//Set visited
		if (currentNode->getIndex() == _end->getIndex())
		{
			path->addWaypoint(_end->getPosition());

			return path;
		}

		nodesVisitedMap.push_back(currentNode->getIndex());

		for(auto nextEdge = nextEdgeVector.cbegin(); nextEdge != nextEdgeVector.cend(); ++nextEdge)
		{
			if (!(*nextEdge)->canTraverse(currentNode))
				continue;

			const unsigned int index = (*nextEdge)->getTarget()->getIndex();
			if (!visited(nodesVisitedMap, index))
				edgeStack.push((*nextEdge));
		}
	}

	return path;
}

bool DepthFirstGraphSearch::visited(const std::vector<unsigned int>& nodeVector, const unsigned int& index) const
{
	for (auto nextNodeIndex = nodeVector.cbegin(); nextNodeIndex != nodeVector.cend(); ++nextNodeIndex)
	{
		if ((*nextNodeIndex) == index)
			return true;
	}
	return false;
}
