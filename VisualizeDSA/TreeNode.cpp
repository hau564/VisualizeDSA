#include "TreeNode.hpp"

TreeNode::TreeNode(std::vector<int> _values) {
	create(_values);
}

TreeNode::~TreeNode()
{
	
}

TreeNode*& TreeNode::Child(int id)
{
	while ((int)childs.size() <= id) 
		childs.push_back(nullptr);
	return childs[id];
}

int TreeNode::getChildCount() const
{
	return childs.size();
}

int TreeNode::getRealChildCount() const
{
	int cnt = 0;
	for (TreeNode* child : childs) {
		if (child) cnt++;
	}
	return cnt;
}

std::vector<TreeNode*> TreeNode::getAllChilds()
{
	return childs;
}

void TreeNode::addChild(TreeNode* child)
{
	childs.push_back(child);
}

void TreeNode::updateHeight()
{
	height = std::max(getChildHeight(0), getChildHeight(1)) + 1;
}

int TreeNode::getChildHeight(int id) 
{
	return Child(id) ? Child(id)->height : -1;
}
