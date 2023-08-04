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

void Tools::Mouse::setWindow(sf::RenderWindow* _window)
{
	window = _window;
}

sf::RenderWindow* Tools::Mouse::window = nullptr;
sf::Vector2f Tools::Mouse::getPosition(sf::RenderWindow& window)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	return sf::Vector2f(worldPos.x, worldPos.y);
}

sf::Vector2f Tools::Mouse::getPosition()
{
	if (!window) return { -100, -100 };
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
	sf::Vector2f worldPos = window->mapPixelToCoords(pixelPos);
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
	char prev = '#';
	for (char c : s) {
		if (v.empty()) v.push_back(0);
		if (c == ',' || c == ' ') {
			if (prev == ',' || prev == ' ') continue;
			v.push_back(0);
			prev = c;
			continue;
		}
		prev = c;
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

bool Tools::String::toVectorEdges(std::string s, std::vector<std::pair<std::pair<int, int>, int>>& v)
{
	v.clear();
	std::vector<int> a;
	if (!isVectorInt(s)) return false;

	a = toVectorInt(s);
	if (a.size() % 3) return false;
	for (int i = 0; i < a.size(); i += 3) {
		v.push_back({ {a[i], a[i + 1]}, a[i + 2] });
	}
	return true;
}

bool getParameters(std::string s, int& i, std::vector<int>& a) {
	if (s[i] == ')') {
		a.clear();
		return true;
	}
	a.assign(1, 0);
	for (; i < (int)s.size() && s[i] != ')'; ++i) {
		if (s[i] == ' ') {
			continue;
		}
		if (s[i] == ',') {
			a.push_back(0);
			continue;
		}
		if (s[i] < '0' || s[i] > '9') return false;
		a.back() = a.back() * 10 + (s[i] - '0');
	}
	return i < (int)s.size() && s[i] == ')';
}

std::string Tools::String::process(std::string &s)
{
	for (int i = (int)s.size() - 1; i >= 0; --i) {
		if (s[i] == '@') {
			if (s.substr(i, 9) == "@randint(") {
				std::vector<int> a;
				int j = i + 9;
				if (!getParameters(s, j, a)) continue;
				if (a.size() > 1) continue;
				int x = 100;
				if (a.size()) x = a[0];
				s.replace(i, j - i + 1, toString(rand() % x));
			}
			else if (s.substr(i, 10) == "@randedge(") {
				std::vector<int> a;
				int j = i + 10;
				if (!getParameters(s, j, a)) continue;
				if (a.size() > 3) continue;
				int x = 100, y = 100, z = 100;
				if (a.size()) {
					x = a[0];
					y = a.back();
				}
				if (a.size() == 3) z = a[2];
				s.replace(i, j - i + 1, toString(rand() % x) + " " + toString(rand() % y) + " " + toString(rand() % z));
			}
			else if (s.substr(i, 11) == "@randarray(") {
				std::vector<int> a;
				int j = i + 11;
				if (!getParameters(s, j, a)) continue;
				if (a.size() > 2) continue;
				int n = rand() % 20;
				if (a.size()) n = a[0];
				int m = 100;
				if (a.size() > 1) m = a[1];
				std::string t = "";
				for (int i = 0; i < n; ++i) {
					t += toString(rand() % m);
					if (i + 1 < n) t += ",";
				}
				s.replace(i, j - i + 1, t);
			}
		}
	}
	return "";
}
