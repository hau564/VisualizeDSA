#include "Button.hpp"
#include "Tools.hpp"
#include "Layout.hpp"

void Button::create(sf::Vector2f _pos, sf::Vector2f _size) {
	for (int i = 0; i < 3; ++i) {
		states.push_back(sf::RoundedRectangleShape(_size, std::min(_size.x, _size.y) / 3, Layout::Button::cornerPointCount));
		states[i].setPosition(_pos);
		setState(Layout::Button::states[i], i);
	}
	setPosition(_pos);
	setSize(_size);
	getStateId = [this](const Button* button) {
		return button->isHolding() ? 2 : (button->isFocusing() ? 1 : 0);
	};
	lastPos = _pos;
}
Button::Button(sf::Vector2f _pos, sf::Vector2f _size)
{
	create(_pos, _size);
}
void Button::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	//update();
	Button::MouseDetection::handleEvent(window, event);
}

void Button::update()
{
	sf::Vector2f pos = getPosition();
	if (abs(pos.x - lastPos.x) > 0.001 || abs(pos.y - lastPos.y) > 0.001) {
		for (sf::RoundedRectangleShape& state : states) {
			state.setPosition(state.getPosition() + pos - lastPos);
			state.scale(getScale());
		}
		lastPos = pos;
	}
	if (text && !specialText) Tools::Text::middleAligning(*text, getPosition(), states[0].getSize(), 1);
	Button::MouseDetection::update();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates _states) const
{
	target.draw(states[getStateId(this)]);
	for (int i = 0; i < (int)getStateIds.size(); ++i) {
		int id = getStateIds[i](this);
		if (id >= 0) target.draw(states[id]);
	}
	if (text) target.draw(*text);
}

void Button::setText(std::string s, std::shared_ptr<sf::Font> font)
{
	text->setFont(*font);
	text->setString(s);
	text->setCharacterSize(states[0].getSize().y / 2);
	text->setFillColor(Layout::Text::fillColor);
	Tools::Text::middleAligning(*text, states[0].getPosition(), states[0].getSize());
}
void Button::setText(const sf::Uint32 s[], std::shared_ptr<sf::Font> font)
{
	specialText = 1;
	text->setFont(*font);
	text->setString(s);
	text->setCharacterSize(states[0].getSize().y / 2);
	text->setFillColor(Layout::Text::fillColor);
	text->setLetterSpacing(-2);
	Tools::Text::middleAligning(*text, getPosition(), states[0].getSize(), 1);
}
void Button::setRadius(float _radius)
{
	for (sf::RoundedRectangleShape& state : states)
		state.setCornersRadius(_radius);
}

void Button::setState(ButtonState state, int id)
{
	while (id >= (int)states.size())
		addState(states[0]);
	states[id].setFillColor(state.fillColor);
	states[id].setOutlineColor(state.outlineColor);
	states[id].setOutlineThickness(state.outlineThickness);
}

void Button::setStates(std::vector<ButtonState> _states)
{
	for (int i = 0; i < (int)_states.size(); ++i)
		setState(_states[i], i);
}

void Button::setFontSize(int size)
{
	if (text) {
		text->setCharacterSize(size);
		Tools::Text::middleAligning(*text, states[0].getPosition(), states[0].getSize());
	}
}

void Button::setTransparency(int alpha)
{
	for (sf::RoundedRectangleShape& state : states) {
		sf::Color color = state.getFillColor();
		color.a = alpha;
		state.setFillColor(color);
	}
	/*if (text) {
		sf::Color color = text->getFillColor();
		color.a = alpha;
		text->setFillColor(color);
	}*/
}

void Button::addState(sf::RoundedRectangleShape newState)
{
	states.push_back(newState);
}

void Button::addGetStateId(std::function<int(const Button*)> getId)
{
	getStateIds.push_back(getId);
}

void Button::removeGetStateId(int i)
{
	if (i < getStateIds.size()) 
		getStateIds.erase(getStateIds.begin() + i);
}

std::string Button::getLabel()
{
	if (!text) return "";
	return text->getString();
}
