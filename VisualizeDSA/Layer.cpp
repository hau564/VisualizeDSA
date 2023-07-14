#include "Layer.hpp"

void Layer::addTree(Tree* tree)
{
	for (Node* node : tree->getNodes()) if (node)
		nodes.push_back(*node);
	for (Edge* edge : tree->getEdges()) if (edge)
		edges.push_back(*edge);
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Edge edge : edges) 
		target.draw(edge, states);
	for (Node node : nodes) 
		target.draw(node, states);
}

std::vector<Node> Layer::getNodes() const
{
	return nodes;
}

std::vector<Edge> Layer::getEdges() const
{
	return edges;
}
