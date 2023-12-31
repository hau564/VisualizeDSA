#pragma once

#ifndef CONTROLBOX_HPP
#define CONTROLBOX_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.hpp"

class ControlBox: public sf::Drawable
{
public:
	void setup();

public:
	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setTimeList(std::vector<float> _timeList);
	void addTime(float _time);

	void start();
	void clear();

	int getCurrent() const;

private:
	void setupButtons();
private:
	sf::RoundedRectangleShape bound;
	Button bplay, bstop, bback, bforw, bstart, bend;
	Button incSpeed, decSpeed;
	
	sf::Text speedText;
	int speed = 1;
	
	std::vector<float> timeList;
	sf::Clock clock;
	int playing, current;
	double timeSinceLast = 0;
};

#endif // !CONTROLBOX_HPP