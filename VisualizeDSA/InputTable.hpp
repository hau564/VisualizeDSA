#pragma once

#ifndef INPUTTABLE_HPP
#define INPUTTABLE_HPP

#include <SFML/Graphics.hpp>
#include "Textbox.hpp"
#include "Input.hpp"

class InputTable: public sf::Drawable
{
public:
	void setup();
	void addTextbox(std::string label);
	void setTextboxes(std::vector<std::string> labels);

	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int newInput = 0;
	void getInput(std::string& label, std::string& input);
private:
	sf::RoundedRectangleShape shape;
	std::vector<Input> inputs;
};

#endif // !INPUTTABLE_HPP