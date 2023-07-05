#pragma once

#ifndef EDGE_HPP
#define EDGE_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"

class Edge: public sf::Drawable
{
public:
	Edge() {};
	~Edge() {};

	void create(sf::Vector2f pos1, sf::Vector2f pos2, float thickness = 5.0f, float dis = 0, sf::Color color = sf::Color::Black);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setDirect(bool _direct);
	void setStart(sf::Vector2f pos);
	void setEnd(sf::Vector2f pos);
private:
	sf::RectangleShape line;
	sf::CircleShape arrow;
	bool direct = true;
	sf::Vector2f pos1, pos2;
};

#endif // !EDGE_HPP