#pragma once

#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"

class TreeNode : public Node
{
public:
	TreeNode(std::vector<int> _values);
	~TreeNode();

	TreeNode*& Child(int id);
	int getChildCount() const;
	std::vector<TreeNode*> getAllChilds();

	void addChild(TreeNode* child);
	void update();

	int getChildHeight(int id);

public:
	std::vector<TreeNode*> childs;
	int height = 0;
};

#endif // !TREENODE_HPP