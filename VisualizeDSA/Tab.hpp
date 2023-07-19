#pragma once

#ifndef TAB_HPP
#define TAB_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.hpp"
#include "StructurePicker.hpp"
#include "StructureRunner.hpp"
#include "Display.hpp"
#include "ControlBox.hpp"

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
	void activate();
	void deactive();

	std::function<int(const Button * button)> defaultId = [&](const Button* button) mutable {
		return ((this->isActive() || button->isHolding() && !xButton.isHolding())) ? 2 : (button->isFocusing() ? 1 : 0);
	};;
public:
	bool isRemove();

public:
	bool isActive() const;

private:
	int id;
	bool active = false, removed = false, added;
	Button xButton;
	StructurePicker structurePicker;
	StructureRunner structureRunner;
	sf::RectangleShape workingArea, cover;
	Display display;
	ControlBox control;
};

#endif // !TAB_HPP