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

	Edge(sf::Vector2f pos1, sf::Vector2f pos2);

	void create(sf::Vector2f pos1, sf::Vector2f pos2, sf::Color color = sf::Color::Black, float thickness = 5.0f, float dis = 0);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setDirect(bool _direct);
	void setStart(sf::Vector2f pos);
	void setEnd(sf::Vector2f pos);

	void setColor(sf::Color color);
	sf::Color getColor();

	// == operator
	bool operator==(const Edge& other) const;

	sf::Vector2f getStart() const;
	sf::Vector2f getEnd() const;
private:
	sf::RectangleShape line;
	sf::CircleShape arrow;
	bool direct = false;
	sf::Vector2f pos1, pos2;
	sf::Color color;
	sf::Text* text;
};

#endif // !EDGE_HPP