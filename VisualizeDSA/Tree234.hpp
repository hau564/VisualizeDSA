#pragma once

#ifndef TREE234_HPP
#define TREE234_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Visualizer.hpp"
#include "Tools.hpp"

class Tree234
{
public:
	~Tree234() {
		std::cout << "deleted Tree234\n";
		Tools::Tree::killTree(root);
	}

	void setup(Visualizer *visualizer);
	void visualize();

private:
	void merge(TreeNode*& node, int id);
	
	void drop(TreeNode*& node);
	void insertBuild(TreeNode*& node, int x);
	void build(std::vector<int> values);

	void dropVisualize(TreeNode*& node);
	void mergeVisualize(TreeNode*& node, int id);
	void insertVisualize(TreeNode*& node, int x);
	void insert(int x);

	void merge3(TreeNode* node, TreeNode *sibNode, TreeNode *idNode);
	bool fix(TreeNode* node, int id);
	void removeValue(TreeNode* node, TreeNode* par);
	void deleteNodeValue(TreeNode*& node, int id, TreeNode* par = nullptr);
	void deleteVisualize(TreeNode*& node, int x, TreeNode *par = nullptr);
	void Delete(int x);

	void search(int x);

	Visualizer* visualizer;
	std::map<int, int> exist;

	TreeNode *root = nullptr;
};

#endif // !TREE234_HPP