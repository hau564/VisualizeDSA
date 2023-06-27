#include "Button.hpp"
#include "Tools.hpp"
#include "Layout.hpp"

void Button::create(sf::Vector2f _pos, sf::Vector2f _size) {
	for (int i = 0; i < 3; ++i) {
		states.push_back(sf::RoundedRectangleShape(_size, std::min(_size.x, _size.y) / 3, Layout::Button::cornerPointCount));
		states[i].setPosition(_pos);
		states[i].setFillColor(Layout::Button::fillColor[i]);
		states[i].setOutlineThickness(Layout::Button::outlineThickness[i]);
		states[i].setOutlineColor(Layout::Button::outlineColor[i]);
	}
	setPosition(_pos);
	setSize(_size);
	getStateId = [this](const Button* button) {
		return button->isHolding() ? 2 : (button->isFocusing() ? 1 : 0);
	};
}
Button::Button(sf::Vector2f _pos, sf::Vector2f _size)
{
	create(_pos, _size);
}
void Button::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	update();
	Button::MouseDetection::handleEvent(window, event);
	for (std::function<void(const Button*)> handle : handles)
		handle(this);
}

void Button::update()
{
	for (sf::RoundedRectangleShape& state : states) {
		state.setPosition(getPosition());
		state.scale(getScale());
	}
	if (text) Tools::Text::middleAligning(*text, getPosition(), states[0].getSize());
	Button::MouseDetection::update();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates _states) const
{
	target.draw(states[getStateId(this)]);
	if (text) target.draw(*text);
}



void Button::setText(std::string s, sf::Font* font)
{
	if (text) delete text;
	text = new sf::Text(s, *font, states[0].getSize().y / 2);
	text->setFillColor(Layout::Text::fillColor);
	Tools::Text::middleAligning(*text, states[0].getPosition(), states[0].getSize());
}
void Button::setRadius(float _radius)
{
	for (sf::RoundedRectangleShape& state : states)
		state.setCornersRadius(_radius);
}

void Button::addHandle(std::function<void(const Button*)> handle)
{
	handles.push_back(handle);
}

void Button::addState(sf::RoundedRectangleShape newState)
{
	states.push_back(newState);
	states.back().setSize(states[0].getSize());
	states.back().setPosition(states[0].getPosition());
}
