#include "Layout.hpp"
#include <iostream>
#include "Color.hpp"

namespace Layout {
	int cornerPointCount = 50;
	int componentSpacing = 10;

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



	namespace WindowComponent {
		sf::Color fillColor = Color::White;
		sf::Color outlineColor = Color::Black;
	}

	namespace DisplayComponent {
		namespace Node {
			float height = 50;
			float fontSize = 30;
			float extraFontSize = 10;
			float valueSpacing = 5;
		}
		namespace Tree {
			float verticalSpacing = 100;
			float horizontalSpacing = 10;
		}
	}

	namespace DisplayScreen {
		sf::Vector2f pos = sf::Vector2f(Tabbar::pos + sf::Vector2f(0, Tabbar::size.y + 5));
		sf::Vector2f size = sf::Vector2f(1450, 930);
		float outlineThickness = 2, cornerRadius = 10;
		sf::Color outlineColor = sf::Color::Black;
		sf::Color fillColor = sf::Color::White;
	}

	namespace ControlBox {
		sf::Vector2f pos = sf::Vector2f(DisplayScreen::pos + sf::Vector2f(0, DisplayScreen::size.y + componentSpacing));
		sf::Vector2f size = sf::Vector2f(1450, 70);
		float outlineThickness = 2, cornerRadius = 10;
		sf::Color outlineColor = sf::Color::Black;
		sf::Color fillColor = sf::Color::White;
		sf::Vector2f buttonSize(60, 60);
		float buttonSpacing = 75;
	}
}