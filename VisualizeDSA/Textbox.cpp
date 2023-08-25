#include "Textbox.hpp"
#include "Tools.hpp"
#include "Layout.hpp"
#include "KeyboardDetection.hpp"
#include "Color.hpp"
void Textbox::create(sf::Vector2f _pos, sf::Vector2f _size)
{
	Button::create(_pos, _size);

	text.setFont(*Resources::Font::courier);
	text.setCharacterSize(_size.y / 2);
	text.setFillColor(Layout::Text::fillColor);
	text.setString("A");
	Tools::Text::leftAligning(text, _pos, _size, 1);
	charWidth = text.getLocalBounds().width;

	aftText.setFont(*Resources::Font::courier);
	aftText.setCharacterSize(_size.y / 2);
	aftText.setFillColor(Layout::Text::fillColor);

	text.setString(inputString);

	cursor.setFont(*Resources::Font::courier);
	cursor.setCharacterSize(_size.y / 2 + 17);
	cursor.setFillColor(Layout::Text::fillColor);
	cursor.setString("|");
	Tools::Text::leftAligning(cursor, _pos, _size, 1);
	//cursor.setPosition(cursor.getPosition() + sf::Vector2f(0, 7));

	sf::Vector2f center = _pos + _size - sf::Vector2f(getSize().y / 2, getSize().y / 2);
	sf::Vector2f size = sf::Vector2f(getSize().y / 2, getSize().y / 2);
	xbutton.create(center - size / 2.f, size);
	xbutton.setRadius(size.x / 2);
	xbutton.setText("X", Resources::Font::arial);
	xbutton.setState({ Layout::workplaceBackground, Layout::workplaceOutline, 0 }, 1);

	clock.restart();
}

void Textbox::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	Button::handleEvent(window, event);
	if ((!active && isFocusing()) || justReleased()) {
		xbutton.handleEvent(window, event);
		if (xbutton.isHolding()) {
			inputString = "";
			aftTextString = "";
		}
	}
	if (isHolding()) {
		active = 1;
	}
	if (justPressedOutside()) {
		active = 0;
		xbutton.handleEvent(window, event);
	}
	static int justPaste = 0;
	if (active) {
		if (event.type == sf::Event::TextEntered) {
			if (justPaste) justPaste = 0;
			else
			{
				cursorState = 1;
				timeCursor = 0;
				if (event.text.unicode == '\b') // Backspace
				{
					if (!inputString.empty())
					{
						inputString.pop_back();
					}
				}
				else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\t') // ASCII Characters
				{
					inputString += static_cast<char>(event.text.unicode);
				}
				if (event.text.unicode == '\r')
				{
					entered = 1;
					active = 0;
					inputString += aftTextString;
					aftTextString = "";
					Tools::String::process(inputString);
				}
				//check tab
				if (event.text.unicode == '\t')
				{
					inputString += recommends[recId].getString();
				}
			}
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Left) {
				if (!inputString.empty()) {
					aftTextString = inputString.back() + aftTextString;
					inputString.pop_back();
				}
				cursorState = 1;
			}
			if (event.key.code == sf::Keyboard::Right) {
				if (!aftTextString.empty()) {
					inputString += aftTextString.front();
					aftTextString.erase(aftTextString.begin());
				}
				cursorState = 1;
			}
			if (event.key.code == sf::Keyboard::Up) {
				recId = (recId - 1 + recommends.size()) % recommends.size();
			}
			if (event.key.code == sf::Keyboard::Down) {
				recId = (recId + 1) % recommends.size();
			}
			if (event.key.code == sf::Keyboard::Delete) {
				if (!aftTextString.empty()) {
					aftTextString.erase(aftTextString.begin());
				}
				cursorState = 1;
			}
		}
		if (KeyboardDetection::isKeyBindingPressed("CTRL_V")) {
			inputString += sf::Clipboard::getString();
			KeyboardDetection::turnOffKeyBinding("CTRL_V");
			justPaste = 1;
		}
		if (inputString.size() * charWidth > getSize().x - 15) {
			int charCnt = (getSize().x - 15) / charWidth - 3;
			text.setString("..." + inputString.substr((int)inputString.size() - charCnt, charCnt));
		}
		else
			text.setString(inputString);

		aftText.setString("A");
		Tools::Text::leftAligning(aftText, {text.getPosition().x + text.getGlobalBounds().width - 5, getPosition().y}, getSize(), 1);
		aftText.setString(aftTextString.substr(0, std::min((float)aftTextString.size(), (getPosition().x + getSize().x - aftText.getPosition().x) / charWidth)));

	}
	if (!active) cursorState = 0, timeCursor = 0;
	cursor.setPosition({ text.getPosition().x + text.getGlobalBounds().width + 5, cursor.getPosition().y });
	//text.setString(inputString + aftTextString);
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
	if ((!active && isFocusing())) 
		xbutton.update();

	if (recId != -1) {
		for (int i = 0; i < (int)recommends.size(); ++i) {
			Tools::Text::leftAligning(recommends[i], recBox.getPosition() + sf::Vector2f(0, (i - recId) * getSize().y), recBox.getSize());
		}
	}
}

void Textbox::addHandle(std::function<void(const Textbox*)> handle)
{
	handles.push_back(handle);
}

void Textbox::setStringRecommend(std::vector<std::string> recs)
{
	sf::Vector2f pos = getPosition(), size = getSize();
	pos.x += size.x + 5;
	size.x *= 0.7f;
	
	recBox.setPosition(pos);
	recBox.setSize(size);
	recBox.setOutlineColor(sf::Color::Black);
	recBox.setOutlineThickness(1);
	recBox.setFillColor(sf::Color::Transparent);
	recBox.setCornersRadius(1);
	recBox.setCornerPointCount(10);

	recId = 0;
	for (int i = 0; i < (int)recs.size(); ++i) {
		recommends.push_back(sf::Text(recs[i], *Resources::Font::courier, size.y / 2));
		recommends.back().setFillColor(Layout::workplaceOutline);
		recommends.back().setOutlineColor(Layout::workplaceBackground);
		recommends.back().setOutlineThickness(3);
		Tools::Text::leftAligning(recommends.back(), pos + 1.f * i * sf::Vector2f(0, size.y), size);
	}
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
	return inputString + aftTextString;
}

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Button::draw(target, states);
	target.draw(text);
	target.draw(aftText);
	if (cursorState) target.draw(cursor);
	if (!active && isFocusing()) {
		target.draw(xbutton);
	}
	if (active && recId != -1) {
		target.draw(recBox, states);
		for (int i = 0; i < (int)recommends.size(); ++i) {
			target.draw(recommends[i], states);
		}
	}
}
