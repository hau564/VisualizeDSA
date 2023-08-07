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

	void addVirtualLayer(float time, std::string s = "");
	void addLayer(Layer layer, float time, std::string s = "");

	void setSource(std::vector<std::string> source);
	
	void start();
	void clear();
	std::vector<Layer> layers;	

	bool isPlaying() const;

private:
	sf::RoundedRectangleShape screenShape;
	ControlBox control;
	int started = 0;

	std::vector<int> idLeft, idRight;

	MouseDetection mouseDetection;
	sf::Vector2f holdingPosition = sf::Vector2f(-1, -1);

	sf::View view;
	float zoomRatio = 1.1f;
	sf::FloatRect viewTarget, baseView;

	std::map<std::string, sf::Text*> textMap;
	std::vector<sf::Text*> corSource;
	sf::Text* prev = nullptr;

	void move(sf::FloatRect& rect, sf::Vector2f delta);
	void zoom(sf::FloatRect& rect, sf::Vector2f mouseRatio, float ratio);
};

#endif // !DISPLAY_HPP