#ifndef KEYBOARDDETECTION_HPP
#define KEYBOARDDETECTION_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>

namespace KeyboardDetection {
	extern std::map<std::string, std::pair<std::vector<int>, int>> keyBindings;
	extern int prevUnicode;
	extern std::set<int> keyHoldings;

	extern void addKeyBinding(std::string name, std::vector<int> keys);
	extern bool isKeyBindingPressed(std::string name);
	extern void turnOffKeyBinding(std::string name);
	extern char getChar();

	extern void handleEvent(sf::RenderWindow &window, sf::Event event);
	extern void update();
}

#endif // !KEYBOARDDETECTION_HPP

