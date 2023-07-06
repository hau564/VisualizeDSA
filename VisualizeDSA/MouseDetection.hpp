#pragma once

#ifndef MOUSEDETECTION_HPP
#define MOUSEDETECTION_HPP

#include <SFML/Graphics.hpp>

class MouseDetection: public sf::Transformable
{
public:
	MouseDetection() {};
	~MouseDetection() {};

public:
	void setSize(sf::Vector2f _size);
	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();

	sf::Vector2f getCenter();

public:
	bool isHolding() const;
	bool isFocusing() const;
	bool justReleased() const;
	bool justReleasedInside() const;
	bool justReleasedOutside() const;
	bool justPressedOutside() const;

	sf::Vector2f getSize() const;
	sf::Vector2f getBoundFrom(sf::Vector2f position) const;

private:
	bool holding = false, focusing = false, prevHolding = false, pressedOutside = false;
	sf::Vector2f size;
};

#endif // !MOUSEDETECTION_HPP