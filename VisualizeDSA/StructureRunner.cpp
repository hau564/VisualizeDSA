#include "StructureRunner.hpp"

void StructureRunner::create(std::string _structName)
{
	structName = _structName;

	visualizer = new Visualizer();
	visualizer->setup();

	structId.emplace("HashTable", 0);
	structId.emplace("AVLTree", 1);
	structId.emplace("234Tree", 2);
	structId.emplace("MaxHeap", 3);
	structId.emplace("Trie", 4);
	structId.emplace("Graph", 5);
	structId.emplace("MinHeap", 3);

	switch (structId[structName]) {
		case 0:
			hashTable = new HashTable();
			hashTable->setup(visualizer);
			break;
		case 1:
			avl = new AVL();
			avl->setup(visualizer);
			break;
		case 2:
			tree234 = new Tree234();
			tree234->setup(visualizer);
			break;
		case 3:
			heap = new Heap();
			heap->setup(visualizer);
			break;
		case 4:
			trie = new Trie();
			trie->setup(visualizer);
			break;
		case 5:
			graph = new Graph();
			graph->setup(visualizer);
			break;
	}
	if (structName == "MinHeap")
		heap->setMinHeap();
} 

void StructureRunner::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	visualizer->handleEvent(window, event);
}

void StructureRunner::update()
{
	visualizer->update();

	switch (structId[structName]) {
	case 0:
		hashTable->visualize();
		break;
	case 1:
		avl->visualize();
		break;
	case 2:
		tree234->visualize();
		break;
	case 3:
		heap->visualize();
		break;
	case 4:
		trie->visualize();
		break;
	case 5:
		graph->visualize();
		break;
	}
}

void StructureRunner::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	visualizer->draw(target, states);
}
