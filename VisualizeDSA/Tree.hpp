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
public:
	TreeNode* root = nullptr;

private:
	void dfsUpdate(TreeNode* node);
	void dfsDraw(const TreeNode* node, sf::RenderTarget& target, sf::RenderStates states) const;
	void dfsEquid(TreeNode* node);
	sf::Vector2f nodePos;
};

#endif // !TREE_HPP