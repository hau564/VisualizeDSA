#include "TreeNode.hpp"
#include <iostream>

TreeNode::TreeNode(std::vector<int> _values)
{
    create(_values);
}

void TreeNode::create(std::vector<int> _values)
{
    Node::create(_values);
}

void TreeNode::update()
{
    Node::update();
    int id = 0;
    for (TreeNode* node : childNodes) {
       	if (node == nullptr) continue;
        childEdges[id]->create(this->getCenter(),node->getBoundFrom(this->getCenter()), 3, 6);
        id++;
    }
}

TreeNode* TreeNode::getChild(int id) const
{
    if ((int)childNodes.size() <= id) return nullptr;
    return childNodes[id];
}

Edge* TreeNode::getEdge(int id) const
{
    if ((int)childEdges.size() <= id) return nullptr;
	return childEdges[id];
}

void TreeNode::addChild(TreeNode* child)
{
    childNodes.push_back(child);
	childEdges.push_back(new Edge());
}

void TreeNode::addChild(int id, TreeNode* child)
{
    while (childNodes.size() <= id) {
        childNodes.push_back(nullptr);
        childEdges.push_back(nullptr);
    }
	childNodes[id] = child;
	childEdges[id] = new Edge();
    childEdges[id]->create(this->getCenter(), child->getPosition());
}

std::vector<TreeNode*> TreeNode::getChilds() const
{
    return childNodes;
}

std::vector<Edge*> TreeNode::getEdges() const
{
    return childEdges;
}
