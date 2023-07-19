#include "Layer.hpp"
#include <queue>

Layer::Layer(TreeNode* root)
{
	addTree(root);
}

void Layer::addTree(TreeNode* root)
{
	if (!root) return;
	std::queue<TreeNode*> q;
	q.push(root);

	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();

		nodes.push_back(*((Node*)node));
		nodes.back().update();

		for (TreeNode* child : node->getAllChilds()) if (child) {
			q.push(child);
			edges.push_back(Edge(node->getCenter(), child->getCenter()));
		}
	}
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

void Layer::clear()
{
	nodes.clear();
	edges.clear();
}

sf::Vector2f Layer::getMaxCoord() const
{
	sf::Vector2f maxCoord = sf::Vector2f(0, 0);
	for (Node node : nodes) {
		sf::Vector2f nodePos = node.getPosition();
		sf::Vector2f nodeSize = node.getSize();
		maxCoord.x = std::max(maxCoord.x, nodePos.x + nodeSize.x);
		maxCoord.y = std::max(maxCoord.y, nodePos.y + nodeSize.y);
	}
	return maxCoord;
}
