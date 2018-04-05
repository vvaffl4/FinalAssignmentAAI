#include "AStarGraphSearch.h"
#include "GraphSearchHeuristic.h"

AStarGraphSearch::AStarGraphSearch()
= default;

AStarGraphSearch::~AStarGraphSearch()
= default;

Path* AStarGraphSearch::searchGraph(const Node* start, const Node* end)
{
	Path* path = new Path(false);

	//Stack of edges
	std::vector<const Node*>		priorityQueue;
	std::vector<unsigned int>		nodesVisitedMap;

	std::map<unsigned int, Edge*>		searchFrontier;		//The next edges to search and possibly added
	std::map<unsigned int, double>		realCostToNode;		//Cost to node with index

	//Starting node
	priorityQueue.push_back(start);

	while (!priorityQueue.empty())
	{
		//Indexed priority queue low
		const Node* currentNode = priorityQueue.front(); 
		const unsigned int fromIndex = currentNode->getIndex();
		priorityQueue.erase(priorityQueue.begin());

		//Move node from searchFrontier to shortestPath
		path->addWaypoint(currentNode->getPosition());

		//if the end has been found
		if (fromIndex == end->getIndex())
			return path;

		nodesVisitedMap.push_back(fromIndex);

		const std::vector<Edge*> nextEdgeVector = currentNode->getEdges();

		//Priority is not empty
		for(auto currentEdge = nextEdgeVector.cbegin(); currentEdge != nextEdgeVector.cend(); ++currentEdge)
		{ 
			//calculate the heuristic cost from current to currentEdge target
			const double heuristicCost = GraphSearchHeuristic::calculateEuclid(end->getPosition(), (*currentEdge)->getTarget()->getPosition());
			
			//calculate the real cost from currentNode to currentEdge target
			const double realCost = realCostToNode[fromIndex] + (*currentEdge)->getTravelCost();
			
			const unsigned int toIndex = (*currentEdge)->getTarget()->getIndex();

			if(searchFrontier[toIndex] == nullptr)
			{
				_totalCostToNode[toIndex]	= (realCost + heuristicCost);
				realCostToNode[toIndex]		= realCost;
				searchFrontier[toIndex]		= *currentEdge;

				priorityQueue.push_back((*currentEdge)->getTarget());
			}
			else if(realCost < realCostToNode[toIndex] && visited(nodesVisitedMap, toIndex))
			{
				_totalCostToNode[toIndex]	= realCost + heuristicCost;
				realCostToNode[toIndex]		= realCost;
				searchFrontier[toIndex]		= *currentEdge;

				priorityQueue.push_back((*currentEdge)->getTarget());
			}
		}

		std::sort(priorityQueue.begin(), priorityQueue.end(), *this);
	}

	return path;
}

bool AStarGraphSearch::operator()(const Node* i, const Node* j)
{
	return _totalCostToNode[i->getIndex()] < _totalCostToNode[j->getIndex()];
}

bool AStarGraphSearch::visited(const std::vector<unsigned>& nodeVector, const unsigned int& index) const
{
	for (auto nextNodeIndex = nodeVector.cbegin(); nextNodeIndex != nodeVector.cend(); ++nextNodeIndex)
	{
		if ((*nextNodeIndex) == index)
			return true;
	}
	return false;
}
