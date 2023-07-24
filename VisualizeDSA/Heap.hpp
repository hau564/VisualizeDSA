#pragma once

#ifndef HEAP_HPP
#define HEAP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Visualizer.hpp"

class Heap
{
public:
	void setup(Visualizer* visualizer);
	void visualize();

private:
	void build(std::vector<int> values);

	void swapVisualize(int i, int j);
	void heapUpVisualize(int &i);
	void insert(int x);

	void heapDownVisualize(int &i);
	void Delete(int x);

	void Get();

	Visualizer* visualizer;
	std::vector<TreeNode*> tree;
	std::function<int(int, int)> cmp = [](int a, int b) { return a >= b; };
};

#endif // !HEAP_HPP