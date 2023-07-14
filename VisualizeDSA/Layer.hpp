#pragma once

#ifndef LAYER_HPP
#define LAYER_HPP

#include <SFML/Graphics.hpp>
#include "Tree.hpp"

class Layer: public sf::Drawable
{
public:
	Layer() {};
	~Layer() {};
	void addTree(Tree* tree);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	std::vector<Node> getNodes() const;
	std::vector<Edge> getEdges() const;

private:
	std::vector<Node> nodes;
	std::vector<Edge> edges;
};

#endif // !LAYER_HPP