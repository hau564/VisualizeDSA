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
	~StructureRunner() {};

	void create(std::string _structName);
	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::string structName;
	std::map<const std::string, const int> structId;

	Visualizer* visualizer;

	HashTable * hashTable = nullptr;
	AVL* avl = nullptr;
	Tree234* tree234 = nullptr;
	Heap* heap = nullptr;
	Trie* trie = nullptr;
	Graph* graph = nullptr;
};

#endif // !STRUCTURERUNNER_HPP