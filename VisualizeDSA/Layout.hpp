#pragma once

#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Resources.hpp"

namespace Layout {
	namespace Button {
		extern int cornerRadius;
		extern int cornerPointCount;
		extern ButtonState states[3];
		extern std::vector<ButtonState> states2;
	}
	namespace Text {
		extern sf::Color fillColor;
	}
	namespace Scroller {
		extern sf::Color backgroundColor;
		extern sf::Color sliderColor;
		extern int thickness;
		extern float scrollSpeed;
	}
	namespace Window {
		extern float width, height;
		extern sf::Color backgroundColor;
	}
	namespace Tab {
		extern sf::Vector2f pos, size;
		extern float radius;
	}
	namespace Tabbar {
		extern sf::Vector2f pos, size;
		extern sf::Color tabFillColor;
	}
}

#endif // !LAYOUT_HPP