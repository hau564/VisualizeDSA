#pragma once

#ifndef TRIE_HPP
#define TRIE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Visualizer.hpp"
#include "Tools.hpp"

class Trie
{
public:
	~Trie() { 
		std::cout << "deleted Trie\n"; 
		Tools::Tree::killTree(root);
	};
	void setup(Visualizer* _visualizer);
	void visualize();

private:
	void insertBuild(TreeNode* root, std::string s);
	void build(std::vector<std::string> values);

	void insertVisualize(TreeNode* node, std::string s);
	void insert(std::string s);

	void deleteVisualize(TreeNode*& node, std::string s, int i = 0);
	void Delete(std::string s);

	TreeNode* searchVisualize(TreeNode* node, std::string s, int i = 0);
	void search(std::string s);

	Visualizer* visualizer;
	TreeNode * root = nullptr;
};

#endif // !TRIE_HPP