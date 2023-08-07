#pragma once

#ifndef STRUCTURERUNNER_HPP
#define STRUCTURERUNNER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Visualizer.hpp"
#include "AVL.hpp"
#include "Tools.hpp"
#include "Tree234.hpp"
#include "Heap.hpp"
#include "Trie.hpp"
#include "HashTable.hpp"
#include "Graph.hpp"

class StructureRunner: public sf::Drawable
{
public:
	StructureRunner() {};
	~StructureRunner() {
		std::cout << "deleted StructureRunner\n";
		if (hashTable)	delete hashTable;
		if (avl)		delete avl;
		if (tree234)	delete tree234;
		if (heap)		delete heap;
		if (trie)		delete trie;
		if (graph)		delete graph;
		if (visualizer)	delete visualizer;
	};

	void create(std::string _structName);
	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::string structName;
	std::map<const std::string, const int> structId;

	Visualizer* visualizer = nullptr;

	HashTable * hashTable = nullptr;
	AVL* avl = nullptr;
	Tree234* tree234 = nullptr;
	Heap* heap = nullptr;
	Trie* trie = nullptr;
	Graph* graph = nullptr;
};

#endif // !STRUCTURERUNNER_HPP