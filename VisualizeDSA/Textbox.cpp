#include "Textbox.hpp"
#include "Tools.hpp"
#include "Layout.hpp"

void Textbox::create(sf::Vector2f _pos, sf::Vector2f _size)
{
	Button::create(_pos, _size);

	text.setFont(*Resources::Font::courier);
	text.setCharacterSize(_size.y / 2);
	text.setFillColor(Layout::Text::fillColor);
	text.setString("A");
	Tools::Text::leftAligning(text, _pos, _size, 1);
	charWidth = text.getLocalBounds().width;

	text.setString(inputString);

	cursor.setFont(*Resources::Font::courier);
	cursor.setCharacterSize(_size.y / 2 + 17);
	cursor.setFillColor(Layout::Text::fillColor);
	cursor.setString("|");
	Tools::Text::leftAligning(cursor, _pos, _size, 1);
	//cursor.setPosition(cursor.getPosition() + sf::Vector2f(0, 7));

	clock.restart();
}

void Textbox::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	Button::handleEvent(window, event);
	if (isHolding()) {
		active = 1;
	}
	if (justPressedOutside()) {
		active = 0;
	}
	if (active) {
		if (event.type == sf::Event::TextEntered) {
			cursorState = 1;
			timeCursor = 0;
			if (event.text.unicode == '\b') // Backspace
			{
				if (!inputString.empty())
				{
					inputString.pop_back();
				}
			}
			else if (event.text.unicode < 128) // ASCII Characters
			{
				inputString += static_cast<char>(event.text.unicode);
			}
			if (event.text.unicode == '\r')
			{
				entered = 1;
				active = 0;
			}
		}
		if (inputString.size() * charWidth > getSize().x - 15) {
			int charCnt = (getSize().x - 15) / charWidth - 3;
			text.setString("..." + inputString.substr((int)inputString.size() - charCnt, charCnt));
		}
		else
			text.setString(inputString);
	}
	if (!active) cursorState = 0, timeCursor = 0;
	cursor.setPosition({ text.getPosition().x + text.getGlobalBounds().width + 5, cursor.getPosition().y });
}

Textbox::Textbox(sf::Vector2f _pos, sf::Vector2f _size)
{
	create(_pos, _size);
}

void Textbox::update()
{
	Button::update();
	timeCursor += clock.restart().asMilliseconds();
	if (timeCursor >= 600) cursorState ^= 1, timeCursor = 0;
	if (!active) cursorState = 0, timeCursor = 0;
}

void Textbox::addHandle(std::function<void(const Textbox*)> handle)
{
	handles.push_back(handle);
}

void Textbox::setFontSize(int fontSize)
{
	sf::Vector2f size = getSize(), pos = getPosition();
	text.setCharacterSize(fontSize);
	Tools::Text::leftAligning(text, pos, size, 1);
	cursor.setCharacterSize(fontSize);
	Tools::Text::leftAligning(cursor, pos, size, 1);
}

std::string Textbox::getString()
{
	return inputString;
}

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Button::draw(target, states);
	target.draw(text);
	if (cursorState) target.draw(cursor);
}
