#pragma once

#include <SFML/Graphics.hpp>
#include "TreeNode.hpp"

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
		extern void setWindow(sf::RenderWindow* window);
		extern sf::Vector2f getPosition(sf::RenderWindow& window);
		extern sf::Vector2f getPosition();
		extern sf::RenderWindow* window;
	}

	namespace String {
		extern std::string toString(int x);
		
		extern bool isInt(std::string s);
		extern int toInt(std::string s);

		extern bool isVectorInt(std::string s);
		extern std::vector<int> toVectorInt(std::string s);	

		extern bool isVectorAlphabet(std::string s);
		extern std::vector<std::string> toVectorString(std::string s);

		extern bool isAlphaString(std::string s);
		extern std::string toAlphaString(std::string s);

		extern bool toVectorEdges(std::string s, std::vector<std::pair<std::pair<int, int>, int>>& v);

		extern std::string process(std::string &s);
	}

	namespace Tree {
		extern void killTree(TreeNode* root);
	}
};

