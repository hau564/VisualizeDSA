#pragma once

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include "ControlBox.hpp"
#include "Layer.hpp"

class Display: public sf::Drawable
{
public:
	void setup();

	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void addLayer(Layer layer, float time);
	
	void start();
	void clear();
	std::vector<Layer> layers;	

private:
	sf::RoundedRectangleShape screenShape;
	ControlBox control;
	int started = 0;

	MouseDetection mouseDetection;
	sf::Vector2f holdingPosition = sf::Vector2f(-1, -1);

	sf::View view;
	float zoomRatio = 1.1f;
	sf::FloatRect viewTarget, baseView;

	void move(sf::FloatRect& rect, sf::Vector2f delta);
	void zoom(sf::FloatRect& rect, sf::Vector2f mouseRatio, float ratio);
};

#endif // !DISPLAY_HPP