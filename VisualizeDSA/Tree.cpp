#include "Tree.hpp"
#include <iostream>
#include "Layout.hpp"

void Tree::update()
{
	dfsUpdate(root);
}

void Tree::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	dfsDraw(root, target, states);
}

void Tree::equidLayout(sf::Vector2f pos)
{
	nodePos = pos;
	dfsEquid(root);
}

void Tree::dfsUpdate(TreeNode* node)
{
	if (node == nullptr) return;
	node->update();
	int id = 0;
	for (TreeNode* child : node->getChilds()) {
		dfsUpdate(child);
	}
}

void Tree::dfsDraw(const TreeNode *node, sf::RenderTarget& target, sf::RenderStates states) const
{
	if (node == nullptr) return;
	int id = 0;
	for (TreeNode* child : node->getChilds()) {
		target.draw(*(node->getEdge(id++)), states);
		dfsDraw(child, target, states);
	}
	target.draw(*node, states);
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
