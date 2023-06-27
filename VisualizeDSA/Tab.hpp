#pragma once

#ifndef TAB_HPP
#define TAB_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.hpp"

class Tab : public Button
{
public:
	Tab() {};
	Tab(int _id);
	~Tab() {};

public:
	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	bool isActive();

private:
	int id;
	bool active = false;
};

#endif // !TAB_HPP