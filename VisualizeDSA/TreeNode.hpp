#pragma once

#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "Edge.hpp"
#include <iostream>

class TreeNode: public Node
{
public:
	TreeNode() {};
	~TreeNode() {
		for (TreeNode* node : childNodes) {
			if (node == nullptr) continue;
			delete node;
		}
		for (Edge* edge : childEdges) {
			if (edge == nullptr) continue;
			delete edge;
		}
	};
	
	TreeNode(std::vector<int> _values);
	void create(std::vector<int> _values);
	void update();

	TreeNode* getChild(int id) const;
	Edge* getEdge(int id) const;
	void addChild(TreeNode* child);
	void addChild(int id, TreeNode* child);

	Node* toNode() const;

	std::vector<TreeNode*> getChilds() const;
	std::vector<Edge*> getEdges() const;

private:
	std::vector<TreeNode*> childNodes;
	std::vector<Edge*> childEdges;
};

#endif // !TREENODE_HPP