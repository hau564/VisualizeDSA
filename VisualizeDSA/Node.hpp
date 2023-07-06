#pragma once

#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>
#include "MouseDetection.hpp"
#include "Edge.hpp"

class Node : public MouseDetection, public sf::Drawable
{
public:
	Node() {};
	Node(std::vector<int> _values) {
		create(_values);
	};
	~Node() {};

	void create(std::vector<int> _values);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RoundedRectangleShape nodeShape;
	
	std::vector<int> values;
	std::vector<sf::Text> valueTexts;
	std::vector<sf::RoundedRectangleShape> valueShapes;

	int counting = 0, height = 0;
	sf::Text countingText, heightText;
};

#endif // NODE_HPP