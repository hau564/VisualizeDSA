#include "Tools.hpp"
#include <iostream>
#include "Layout.hpp"

void Tools::Text::middleAligning(sf::Text& text, sf::Vector2f pos, sf::Vector2f size, bool isCourier) {
	float height = text.getLocalBounds().height;
	if (!isCourier) {
		std::string s = text.getString();
		text.setString("ÂÖgq|");
		height = text.getLocalBounds().height;
		text.setString(s);
	}

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f);		
}

void Tools::Text::leftAligning(sf::Text& text, sf::Vector2f pos, sf::Vector2f size, bool isCourier)
{
	float height = text.getLocalBounds().height;
	if (!isCourier) {
		std::string s = text.getString();
		text.setString("ÂÖgq|");
		height = text.getLocalBounds().height;
		text.setString(s);
	}
	
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left, textRect.top + height / 2.0f);
	text.setPosition(pos.x + size.y / 5, pos.y + size.y / 2.0f);
}

sf::Vector2f Tools::Arrangment::horizontal(sf::Vector2f pos, sf::Vector2f size, int spacing) {
	return sf::Vector2f(pos.x + size.x + spacing, pos.y);
}

sf::Vector2f Tools::Arrangment::vertical(sf::Vector2f pos, sf::Vector2f size, int spacing)
{
	return sf::Vector2f(pos.x, pos.y + size.y + spacing);
}

sf::Vector2f Tools::Mouse::getPosition(sf::RenderWindow& window)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	return sf::Vector2f(worldPos.x, worldPos.y);
}

std::string Tools::String::toString(int x)
{
	std::string s = "";
	while (x) {
		s += (char)(x % 10 + '0');
		x /= 10;
	}
	std::reverse(s.begin(), s.end());
	return s;
}
