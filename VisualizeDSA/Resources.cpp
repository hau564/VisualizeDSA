#include "Resources.hpp"

namespace Resources {
	namespace Font {
		std::shared_ptr<sf::Font> arial = std::make_shared<sf::Font>();
		std::shared_ptr<sf::Font> courier = std::make_shared<sf::Font>();
		void load() {
			arial->loadFromFile("Resources/Fonts/arial.ttf");
			courier->loadFromFile("Resources/Fonts/cour.ttf");
		}
	}
	namespace Textures {
		const std::string ds[8] = { "HashTable", "BinarySearchTree", "AVLTree", "23Tree", "234Tree", "Heap", "Trie", "Graph" };
		std::map<std::string, std::unique_ptr<sf::Texture>> textureMap;
		void load() {
			for (int i = 0; i < 8; ++i) {
				std::unique_ptr<sf::Texture> texture(new sf::Texture());
				texture->loadFromFile((const std::string)("Resources/Images/" + ds[i] + ".png"));
				textureMap.insert(std::make_pair(ds[i], std::move(texture)));
			}
		}
		sf::Texture& getTexture(const std::string &name)
		{
			auto found = textureMap.find(name);
			if (found == textureMap.end())
				throw std::runtime_error("No texture with name " + name);
			return *found->second;
		}
	}
}