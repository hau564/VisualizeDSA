#pragma once

#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Visualizer.hpp"

class HashTable
{
public:
	void setup(Visualizer* _visualizer);
	void visualize();

private:
	void create(int _n);
	void insert(int _x);
	void Delete(int _x);

	int mainSearch(int _x);
	void search(int _x);

	std::vector<TreeNode*> arr;
	Visualizer * visualizer;
};

#endif // !HASHTABLE_HPP