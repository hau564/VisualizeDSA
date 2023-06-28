#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include "Tab.hpp"

class Window
{
public:
	Window() {};
	~Window() {};

	void setup();
	void launch();

	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	void draw(sf::RenderWindow &window);

	void addTab();

public:
	sf::Vector2f getNewSlot();
	int getTabCount();
	Button newTab;

private:
	std::vector<Tab> tabs;
};

#endif // !WINDOW_HPP

