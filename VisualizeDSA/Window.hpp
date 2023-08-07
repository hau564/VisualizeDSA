#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include "Tab.hpp"

class Window
{
public:
	Window() {};
	~Window() { std::cout << "deleted Window\n"; };

	void setup();
	void launch();

	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	void draw(sf::RenderWindow &window);

	void addTab();
	std::function<int(const Button *button)> controlFocusTab;

public:
	sf::Vector2f getNewSlot();
	int getTabCount();
	Button newTab;

private:
	std::vector<Tab> tabs;
};

#endif // !WINDOW_HPP

