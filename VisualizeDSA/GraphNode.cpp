#include "GraphNode.hpp"

GraphNode::GraphNode(std::vector<int> values)
{
	create(values);
}

void GraphNode::addAdjacency(GraphNode* node)
{
	adj.push_back(node);
}

std::vector<GraphNode*> GraphNode::getAdjacencies()
{
	return adj;
}
