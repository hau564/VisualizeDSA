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
	Node(sf::Vector2f _pos, std::vector<int> values = {0});
	~Node() {};

	void create(std::vector<int> _values);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	int getValue(int id = 0) const;
	std::vector<int> getValues() const;
	int& Value(int id = 0);

	void setColor(sf::Color color);
	sf::Color getColor() const;

	void memorizePosition();
	sf::Vector2f getOldPosition() const;
	sf::Vector2f getOldCenter() const;

	bool operator==(const Node& other) const;

private:
	sf::RoundedRectangleShape nodeShape;
	
	std::vector<int> values;
	std::vector<sf::Text> valueTexts;
	std::vector<sf::RoundedRectangleShape> valueShapes;

	int counting = 0, height = 0;
	sf::Text countingText, heightText;
	sf::Color color;
	sf::Vector2f memPos;
};

#endif // NODE_HPP