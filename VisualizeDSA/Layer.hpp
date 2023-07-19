#pragma once

#ifndef LAYER_HPP
#define LAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Node.hpp"
#include "Edge.hpp"
#include "TreeNode.hpp"

class Layer: public sf::Drawable
{
public:
	Layer() {};
	~Layer() {};

	Layer(TreeNode* root);
	void addTree(TreeNode* root);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	std::vector<Node> getNodes() const;
	std::vector<Edge> getEdges() const;

	void clear();

	sf::Vector2f getMaxCoord() const;

public:
	std::vector<Node> nodes;
	std::vector<Edge> edges;
};

#endif // !LAYER_HPP