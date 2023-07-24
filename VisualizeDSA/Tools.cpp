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
	if (!x) return "0";
	std::string s = "";
	while (x) {
		s += (char)(x % 10 + '0');
		x /= 10;
	}
	std::reverse(s.begin(), s.end());
	return s;
}

bool Tools::String::isInt(std::string s)
{
	for (char c : s) {
		if (c == ' ') continue;
		if (c < '0' || c > '9') return false;
	}
	return true;
}

int Tools::String::toInt(std::string s)
{
	int x = 0;
	for (char c : s) {
		if (c == ' ') continue;
		x = x * 10 + (c - '0');
	}
	return x;
}

bool Tools::String::isVectorInt(std::string s)
{
	for (char c : s) {
		if (c == ' ') continue;
		if (c == ',') continue;
		if (c < '0' || c > '9') return false;
	}
	return true;
}

std::vector<int> Tools::String::toVectorInt(std::string s)
{
	std::vector<int> v;

	for (char c : s) {
		if (c == ' ') continue;
		if (v.empty()) v.push_back(0);
		if (c == ',') {
			v.push_back(0);
			continue;
		}
		v.back() = v.back() * 10 + (c - '0');
	}
	return v;
}

bool Tools::String::isVectorAlphabet(std::string s)
{
	for (char c : s) {
		if (c == ' ') continue;
		if (c == ',') continue;
		if (c < 'a' || c > 'z') return false;
	}
	return true;
}

std::vector<std::string> Tools::String::toVectorString(std::string s)
{
	std::vector<std::string> v;

	for (char c : s) {
		if (c == ' ') continue;
		if (v.empty()) v.push_back("");
		if (c == ',') {
			v.push_back("");
			continue;
		}
		v.back() += c;
	}
	return v;
}

bool Tools::String::isAlphaString(std::string s)
{
	for (char c : s) if (c < 'a' || c > 'z') return false;
	return true;
}

std::string Tools::String::toAlphaString(std::string s)
{
	std::string res = "";
	for (char c : s) if (c >= 'a' && c <= 'z') res += c;
	return res;
}
