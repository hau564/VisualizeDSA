#pragma once

#ifndef AVL_HPP
#define AVL_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Visualizer.hpp"
#include "TreeNode.hpp"
#include "Tools.hpp"

class AVL {
public:
	~AVL() {
		std::cout << "deleted AVL\n";
		Tools::Tree::killTree(root);
	};

	void setup(Visualizer* visualizer);
	void visualize();

private:
	void rotateRight(TreeNode*& root);
	void rotateLeft(TreeNode*& root);
	void insertBuild(TreeNode*& root, int x);
	void build(std::vector<int> values);

	void rotateRightVisualize(TreeNode*& node);
	void rotateLeftVisualize(TreeNode*& node);
	void balanceVisualize(TreeNode *& node);
	void insertVisualize(TreeNode*& node, int x);
	void insert(int x);

	void deleteNode(TreeNode *& node);
	void deleteVisualize(TreeNode*& node, int x);
	void Delete(int x);

	void search(int x);

	Visualizer* visualizer = nullptr;
	TreeNode* root = nullptr;
};

#endif // !AVL_HPP