#pragma once

#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"

namespace Layout {
	namespace Button {
		extern sf::Color fillColor[3];
		extern int outlineThickness[3];
		extern sf::Color outlineColor[3];
		extern int cornerRadius;
		extern int cornerPointCount;
		extern ButtonState states[3];
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
	namespace Screen {
		extern int width, height;
		extern sf::Color backgroundColor;
	}
	namespace Font {
		extern std::shared_ptr<sf::Font> arial, courier;
		extern void load();
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