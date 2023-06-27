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

	void launch();

public:
	sf::Vector2f getNewSlot();
	int getTabCount();

private:
	sf::RenderWindow window;
	std::vector<Tab> tabs;
};

#endif // !WINDOW_HPP

