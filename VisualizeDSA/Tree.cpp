#include "Tree.hpp"
#include <iostream>
#include "Layout.hpp"
#include <queue>

void Tree::update()
{
	std::queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();
		node->update();
		for (TreeNode* child : node->getChilds()) {
			q.push(child);
		}
	}
}

void Tree::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();
		for (Edge* edge : node->getEdges()) {
			target.draw(*edge, states);
		}
		std::cout << node->getValue() << " " << node->getPosition().x << " " << node->getPosition().y << std::endl;
		target.draw(*node, states);
		for (TreeNode* child : node->getChilds()) {
			q.push(child);
		}
	}
}

void Tree::equidLayout(sf::Vector2f pos)
{
	nodePos = pos;
	dfsEquid(root);
	update();
}

std::vector<Node*> Tree::getNodes() const
{
	std::vector<Node*> nodes;
	std::queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();
		nodes.push_back((Node*)node);
		for (TreeNode* child : node->getChilds()) {
			q.push(child);
		}
	}
	return nodes;
}

std::vector<Edge*> Tree::getEdges() const
{
	std::vector<Edge*> edges;
	std::queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();
		for (Edge* edge : node->getEdges()) {
			edges.push_back(edge);
		}
		for (TreeNode* child : node->getChilds()) {
			q.push(child);
		}
	}
	return edges;
}

void Tree::dfsEquid(TreeNode* node)
{
	if (node == nullptr) return;
	std::vector<TreeNode*> childs = node->getChilds();
	int childCount = childs.size();
	
	nodePos.y += Layout::DisplayComponent::Tree::verticalSpacing;
	for (int i = 0; i < childCount / 2; ++i) {
		dfsEquid(childs[i]);
	}
	nodePos.y -= Layout::DisplayComponent::Tree::verticalSpacing;

	node->setPosition(sf::Vector2f(nodePos));
	nodePos.x += node->getSize().x + Layout::DisplayComponent::Tree::horizontalSpacing;

	nodePos.y += Layout::DisplayComponent::Tree::verticalSpacing;
	for (int i = childCount / 2; i < childCount; ++i) {
		dfsEquid(childs[i]);
	}
	nodePos.y -= Layout::DisplayComponent::Tree::verticalSpacing;
}
