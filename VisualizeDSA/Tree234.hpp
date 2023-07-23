#pragma once

#ifndef TREE234_HPP
#define TREE234_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Visualizer.hpp"

class Tree234
{
public:
	void setup(Visualizer *visualizer);
	void visualize();

private:
	void merge(TreeNode*& node, int id);
	void drop(TreeNode*& node);
	void insertBuild(TreeNode*& node, int x);
	void build(std::vector<int> values);

	void mergeVisualize(TreeNode*& node, int id);
	void insertVisualize(TreeNode*& node, int x);
	void insert(int x);

	Visualizer* visualizer;

	TreeNode *root = nullptr;
};

#endif // !TREE234_HPP