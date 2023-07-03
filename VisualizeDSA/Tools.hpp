#pragma once

#include <SFML/Graphics.hpp>

namespace Tools{
	namespace Text {
		extern void middleAligning(sf::Text& text, sf::Vector2f pos, sf::Vector2f size, bool isCourier = 0);
		extern void leftAligning(sf::Text& text, sf::Vector2f pos, sf::Vector2f size, bool isCourier = 0);
	}

	namespace Arrangment {
		extern sf::Vector2f horizontal(sf::Vector2f pos, sf::Vector2f size, int spacing = 1);
		extern sf::Vector2f vertical(sf::Vector2f pos, sf::Vector2f size, int spacing = 1);
	}

	namespace Mouse {
		extern sf::Vector2f getPosition(sf::RenderWindow& window);
	}

	namespace String {
		extern std::string toString(int x);
	}
};

