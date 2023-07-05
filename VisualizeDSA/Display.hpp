#pragma once

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SFML/Graphics.hpp>

class Display: public sf::Drawable
{
public:
	void setup();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::RoundedRectangleShape screenShape;
private:
};

#endif // !DISPLAY_HPP