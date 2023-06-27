#include "KeyboardDetection.hpp"

namespace KeyboardDetection {
	std::map<std::string, std::pair<std::vector<int>, int>> keyBindings;
	int prevUnicode = -1;
	std::set<int> keyHoldings;

	void addKeyBinding(std::string name, std::vector<int> keys)
	{
		if (keyBindings.find(name) != keyBindings.end()) {
			std::cout << "Key binding name [" << name << "] already exists" << std::endl;
			return;
		}
		keyBindings[name] = std::make_pair(keys, 0);
	}

	bool isKeyBindingPressed(std::string name)
	{
		std::pair<std::vector<int>, int> get = keyBindings[name];
		return get.second >= get.first.size() && keyHoldings.size() == get.first.size();
	}

	char getChar()
	{
		return (char)(prevUnicode);
	}

	void handleEvent(sf::RenderWindow& window, sf::Event event)
	{
		update();
		if (event.type == sf::Event::TextEntered) {
			prevUnicode = event.text.unicode;
		}
		else if (event.type == sf::Event::KeyPressed) {
			keyHoldings.insert(event.key.code);
			for (auto& keyBinding : keyBindings) {
				std::pair<std::vector<int>, int> get = keyBinding.second;
				if (get.second >= get.first.size()) continue;
				if (get.first[get.second] == event.key.code) {
					get.second++;
					keyBinding.second = get;
				}
			}
		}
		else if (event.type == sf::Event::KeyReleased) {
			keyHoldings.erase(event.key.code);
			for (auto& keyBinding : keyBindings) {
				std::pair<std::vector<int>, int> get = keyBinding.second;
				int x = 0;
				while (x < get.second && get.first[x] != event.key.code) x++;
				get.second = x;
				keyBinding.second = get;
			}
		}
	}
	void update()
	{
		prevUnicode = -1;
	}
}