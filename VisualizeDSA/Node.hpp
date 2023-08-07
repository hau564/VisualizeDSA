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
	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void addValue(int x);
	void sortValue();
	void setStringNode(int x = 1);
	void removeValue(int id = 0);

	int getValue(int id = 0) const;
	int getValueCount() const;
	std::vector<int> getValues() const;
	int& Value(int id = 0);

	void setColor(sf::Color color);
	sf::Color getColor() const;

	void memorizePosition();
	sf::Vector2f getOldPosition() const;
	sf::Vector2f getOldCenter() const;

	sf::RoundedRectangleShape& Shape();

	bool operator==(const Node& other) const;

	void showHeight(int t);

	bool stringNode = 0;
	int counting = 0, height = 0;

private:
	sf::RoundedRectangleShape nodeShape;
	
	std::vector<int> values;
	std::vector<sf::Text> valueTexts;
	std::vector<sf::RoundedRectangleShape> valueShapes;

	sf::Text* countingText = nullptr, *heightText = nullptr;
	sf::Color color;
	sf::Vector2f memPos, memCen;

	sf::Vector2f holdingPosition = { -1, -1 };
};

#endif // NODE_HPP