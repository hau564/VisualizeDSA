#pragma once

#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Display.hpp"
#include "InputTable.hpp"
#include "TreeNode.hpp"
#include "Layout.hpp"
#include "Color.hpp"

class Visualizer: public sf::Drawable, public Display, public InputTable 
{
public:
	void setup();
	
	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	void layoutTree(TreeNode* root, sf::Vector2f _pos = Layout::DisplayScreen::basePos);
	
	
	void newStep();
	void newStep(TreeNode* root);
	void duplicateState();

	void addTree(TreeNode* root);

	void moveEdge(Node* u, Node* v, Node* i, Node* j);
	void moveEdge(sf::Vector2f u, sf::Vector2f v, sf::Vector2f uu, sf::Vector2f vv);
	void removeEdge(sf::Vector2f u, sf::Vector2f v);
	void removeEdgeFromParent(Node* v);
	void removeEdgeFromParent(sf::Vector2f v);

	void moveNode(sf::Vector2f pos1, sf::Vector2f pos2, std::vector<int> values = {0});
	void removeNode(TreeNode *node);
	void removeNode(sf::Vector2f pos);

	void highlightNode(Node* node, sf::Color color = Color::highlight);
	void highlightEdge(Node* u, Node* v, sf::Color color = Color::highlight);

	void reArrange(TreeNode *root, int autoDelete = 0, int reLayout = 1);

private:
	sf::Vector2f treePos;
	int index = -1;
	int fps = 30;
};

#endif // !VISUALIZER_HPP