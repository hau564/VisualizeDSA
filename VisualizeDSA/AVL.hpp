#pragma once

#ifndef AVL_HPP
#define AVL_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Visualizer.hpp"
#include "TreeNode.hpp"

class AVL {
public:
	void setup(Visualizer& visualizer);
	void visualize();

private:
	void build(std::vector<int> values);

	void rotateRightVisualize(TreeNode*& node);
	void rotateLeftVisualize(TreeNode*& node);
	void balanceVisualize(TreeNode *& node);
	void insertVisualize(TreeNode*& node, int x);
	void insert(int x);

	void deleteNode(TreeNode *& node);
	void deleteVisualize(TreeNode*& node, int x);
	void Delete(int x);

	TreeNode* searchVisualize(TreeNode*& node, int x);
	void search(int x);

	Visualizer* visualizer;
	TreeNode* root = nullptr;
};

#endif // !AVL_HPP