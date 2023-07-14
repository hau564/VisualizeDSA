#pragma once

#ifndef STRUCTURERUNNER_HPP
#define STRUCTURERUNNER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Display.hpp"
#include "ControlBox.hpp"

class StructureRunner: public sf::Drawable
{
public:
	StructureRunner() {};
	~StructureRunner() {};

	void create(std::string _structName);
	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::string structName;

	Display display;
	ControlBox control;
};

#endif // !STRUCTURERUNNER_HPP