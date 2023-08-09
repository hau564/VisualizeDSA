#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.hpp"
#include "MouseDetection.hpp"
class StructurePicker : public sf::Drawable
{
public:
	StructurePicker() {};
	~StructurePicker() {};

	void create();
	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;	

public:
	std::string getPicked() const;

private:
	std::string stringPicked = "#";
	std::string names[6] = {"HashTable", "AVLTree", "234Tree", "Heap", "Trie", "Graph"};
	std::vector<Button> buttons;
	std::vector<sf::Sprite> sprites;
	MouseDetection workPlace;

	int focusId = 0, n = 6;
	Button start, minHeap, maxHeap;
};

