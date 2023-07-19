#include "InputTable.hpp"
#include "Layout.hpp"
#include "Tools.hpp"

void InputTable::setup()
{
	shape.setFillColor(Layout::InputTable::fillColor);
	shape.setOutlineColor(Layout::InputTable::outlineColor);
	shape.setOutlineThickness(Layout::InputTable::outlineThickness);
	shape.setCornersRadius(Layout::InputTable::cornerRadius);
	shape.setCornerPointCount(50);
	shape.setSize(Layout::InputTable::size);
	shape.setPosition(Layout::InputTable::pos);
}

void InputTable::addTextbox(std::string label)
{
	sf::Vector2f pos = Layout::InputTable::pos + sf::Vector2f(Layout::InputTable::spacing, Layout::InputTable::spacing);
	pos.y += (int)inputs.size() * (Layout::InputTable::labelSize.y + Layout::InputTable::spacing);
	inputs.push_back(Input());
	inputs.back().create(pos, Layout::InputTable::labelSize, label);
	shape.setSize(sf::Vector2f(Layout::InputTable::size.x, Layout::InputTable::spacing + (int)inputs.size() * (Layout::InputTable::spacing + Layout::InputTable::labelSize.y)));
}

void InputTable::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	for (Input& input : inputs) {
		input.handleEvent(window, event);
		if (input.newInput) newInput = 1;
	}
}

void InputTable::update()
{
	for (Input& input : inputs) input.update();
}

void InputTable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
	for (const Input& input : inputs) target.draw(input);
}

void InputTable::getInput(std::string& label, std::string& inputString)
{
	for (Input& input: inputs) {
		if (input.newInput) {
			label = input.getLabel();
			inputString = input.getInput();
			newInput = 0;
			return;
		}
	}
}
