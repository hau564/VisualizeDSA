#pragma once

#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <SFML/Graphics.hpp>

namespace Resources {
	namespace Font {
		extern std::shared_ptr<sf::Font> arial, courier, monospace;
		extern void load();
	}
	namespace Textures {
		extern const std::string ds[8];// = { "HashTable", "BinarySearchTree", "AVLTree", "23Tree", "234Tree", "Heap", "Trie", "Graph" };
		extern std::map<std::string, std::unique_ptr<sf::Texture>> textureMap;
		extern void load();
		extern sf::Texture& getTexture(const std::string &name);
	}
}


#endif // !RESOURCES_HPP