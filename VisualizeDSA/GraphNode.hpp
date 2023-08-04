#pragma once

#ifndef GRAPHNODE_HPP
#define GRAPHNODE_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"

class GraphNode : public Node
{
public:
	GraphNode(std::vector<int> values);
	void addAdjacency(GraphNode* node);
	std::vector<GraphNode*> getAdjacencies();
private:
	std::vector<GraphNode*> adj;
};

#endif // !GRAPHNODE_HPP