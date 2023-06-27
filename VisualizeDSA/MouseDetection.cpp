#include "MouseDetection.hpp"
#include "Tools.hpp"
#include <iostream>

void MouseDetection::setSize(sf::Vector2f _size)
{
	size = _size;
}

void MouseDetection::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	prevHolding = holding;
	sf::FloatRect rect = getTransform().transformRect(sf::FloatRect(sf::Vector2f(0, 0), size));
	sf::Vector2f mousePosition = Tools::Mouse::getPosition(window);
	if (rect.contains(mousePosition)) focusing = 1;
	else focusing = 0;
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (focusing) holding = 1;
		else {
			pressedOutside = 1;
		}
	}
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		holding = 0;
	}
}

void MouseDetection::update()
{
	prevHolding = holding;
	pressedOutside = false;
}

bool MouseDetection::isHolding() const
{
	return holding;
}

bool MouseDetection::isFocusing() const
{
	return focusing;
}

bool MouseDetection::justReleased() const
{
	return prevHolding && !holding;
}

bool MouseDetection::justReleasedInside() const
{
	return prevHolding && !holding && focusing;
}

bool MouseDetection::justReleasedOutside() const
{
	return prevHolding && !holding && !focusing;
}

bool MouseDetection::justPressedOutside() const
{
	return pressedOutside;
}

sf::Vector2f MouseDetection::getSize() const
{
	return sf::Vector2f(size.x * Transformable::getScale().x, size.y * Transformable::getScale().y);
}
