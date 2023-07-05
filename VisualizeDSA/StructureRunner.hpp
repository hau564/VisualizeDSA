#pragma once

#ifndef STRUCTURERUNNER_HPP
#define STRUCTURERUNNER_HPP

#include <SFML/Graphics.hpp>

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

	sf::RoundedRectangleShape displayWindow;
	sf::RoundedRectangleShape inputWindow;
	sf::RoundedRectangleShape sourceWindow;

};

#endif // !STRUCTURERUNNER_HPP