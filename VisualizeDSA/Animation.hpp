#pragma once

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Layer.hpp"

namespace Animation {
	extern float getFloat(float x, float y, float r);
	extern sf::Vector2f getVector2f(sf::Vector2f p1, sf::Vector2f p2, float r);
	extern sf::Color getColor(sf::Color c1, sf::Color c2, float r);

	extern Node getNode(Node n1, Node n2, float r);
	extern Edge getEdge(Edge e1, Edge e2, float r);
	extern Layer getLayer(Layer l1, Layer l2, float r);
}

#endif // !ANIMATION_HPP
