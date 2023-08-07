#pragma once

#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Resources.hpp"

namespace Layout {
	extern int cornerPointCount;
	extern int componentSpacing;
	
	extern sf::Color backgroundColor;
	extern sf::Color workplaceBackground;
	extern sf::Color workplaceOutline;

	namespace Button {
		extern int cornerRadius;
		extern int cornerPointCount;
		extern ButtonState states[3];
		extern std::vector<ButtonState> states2;
	}
	namespace Text {
		extern sf::Color fillColor;
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

	namespace WindowComponent {
		extern sf::Color fillColor;
		extern sf::Color outlineColor;
	}

	namespace DisplayComponent {
		namespace Node {
			extern float height;
			extern float fontSize;
			extern float extraFontSize;
			extern float valueSpacing;
		}
		namespace Tree {
			extern float verticalSpacing;
			extern float horizontalSpacing;
		}
	}

	namespace DisplayScreen {
		extern sf::Vector2f pos, size;
		extern float outlineThickness, cornerRadius;
		extern sf::Color outlineColor, fillColor;
		extern sf::Vector2f basePos;
	}

	namespace ControlBox {
		extern sf::Vector2f pos, size;
		extern float outlineThickness, cornerRadius;
		extern sf::Color outlineColor, fillColor;
		extern sf::Vector2f buttonSize;
		extern float buttonSpacing;
	}

	namespace InputTable {
		extern sf::Vector2f pos, size;
		extern float outlineThickness, cornerRadius;
		extern sf::Color outlineColor, fillColor;
		extern float spacing;
		extern int fontSize;
		extern sf::Vector2f labelSize;
		//extern sf::Vector2f buttonSize;
	}
}

#endif // !LAYOUT_HPP