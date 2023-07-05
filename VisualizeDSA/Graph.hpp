#pragma once

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>

class Graph : public sf::Drawable
{
public:
	Graph() {};
	~Graph() {};
	void create(sf::Vector2f pos, sf::Vector2f size, sf::Color color = sf::Color::Black, float thickness = 5.0f);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
};

#endif // !GRAPH_HPP