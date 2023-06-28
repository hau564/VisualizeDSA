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
	void create(int _id);

public:
	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void updateId(int _id);
	void deactive();
public:
	bool isRemove();

public:
	bool isActive();

private:
	int id;
	bool active = false, removed = false;;
	Button xButton;
};

#endif // !TAB_HPP