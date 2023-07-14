#pragma once

#ifndef TREE_HPP
#define TREE_HPP

#include <SFML/Graphics.hpp>
#include "TreeNode.hpp"

class Tree: public sf::Drawable
{
public:
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void equidLayout(sf::Vector2f pos);

	std::vector<Node*> getNodes() const;
	std::vector<Edge*> getEdges() const;
public:
	TreeNode* root = nullptr;

private:
	void dfsEquid(TreeNode* node);
	sf::Vector2f nodePos;
};

#endif // !TREE_HPP