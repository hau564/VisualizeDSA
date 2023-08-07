#pragma once

#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/Graphics.hpp>
#include "Textbox.hpp"
#include "Button.hpp"

class Input: public sf::Drawable
{
public:
	void create(sf::Vector2f pos, sf::Vector2f size, std::string label);
	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::string getInput();
	std::string getLabel();
	int newInput = 0;
public:
	Textbox textbox;
	Button labelButton;
};

#endif // !INPUT_HPP