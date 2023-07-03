#include "Layout.hpp"
#include <iostream>
#include "Color.hpp"

namespace Layout {
	namespace Window {
		float width = 1920, height = 1080;
		sf::Color backgroundColor = Color::GrayBG;
	}

	namespace Button {
		int cornerRadius = 10;
		int cornerPointCount = 50;
		ButtonState states[3] = {
			{Color::DarkGray, Color::Black, 0},
			{Color::LightGray, Color::Black, 0},
			{Color::White, Color::Black, 0}
		};
		std::vector<ButtonState> states2 = {
			{Color::White, Color::Black, 0.4},
			{Color::LightGray, Color::Black, 0},
			{Color::GrayBG, Color::Black, 0}
		};
	}

	namespace Text {
		sf::Color fillColor = sf::Color::Black;
	}

	namespace Scroller {
		sf::Color backgroundColor = sf::Color(200, 200, 200);
		sf::Color sliderColor = sf::Color(150, 150, 150);
		int thickness = 10;
		float scrollSpeed = 10.0f;
	}

	namespace Tab {
		sf::Vector2f pos = sf::Vector2f(5, 5);
		sf::Vector2f size = sf::Vector2f(200, 50);
		float radius = 10;
	}

	namespace Tabbar {
		sf::Vector2f pos = sf::Vector2f(5, 5);
		sf::Vector2f size = sf::Vector2f(0, 50);
		sf::Color tabFillColor = sf::Color(200, 200, 200);
	}
}