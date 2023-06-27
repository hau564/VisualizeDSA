#include "Layout.hpp"
#include <iostream>
#include "Color.hpp"

namespace Layout {
	namespace Screen {
		int width = 1920, height = 1080;
		sf::Color backgroundColor = Color::GrayBG;
	}

	namespace Button {
		sf::Color fillColor[3] = {
			sf::Color(255, 255, 255),
			sf::Color(240, 240, 240),
			sf::Color(200, 200, 200)
		};
		int outlineThickness[3] = { 0, 1, 1 };
		sf::Color outlineColor[3] = {
			sf::Color(0, 0, 0),
			sf::Color(0, 0, 0),
			sf::Color(0, 0, 0)
		};
		int cornerRadius = 10;
		int cornerPointCount = 50;
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

	namespace Font {
		sf::Font arial, courier;
		void load() {
			arial.loadFromFile("font/arial.ttf");
			courier.loadFromFile("font/cour.ttf");
		}
	}

	namespace Tab {
		sf::Vector2f pos = sf::Vector2f(5, 5);
		sf::Vector2f size = sf::Vector2f(200, 50);
		float radius = size.y / 2;
	}

	namespace Tabbar {
		sf::Vector2f pos = sf::Vector2f(5, 5);
		sf::Vector2f size = sf::Vector2f(0, 50);
		sf::Color tabFillColor = sf::Color(200, 200, 200);
	}
}