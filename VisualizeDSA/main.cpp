#include "VisualizeDSA.hpp"


void setup() {
	Resources::Font::load();
	Resources::Textures::load();
	KeyboardDetection::addKeyBinding("CTRL_TAB", { sf::Keyboard::LControl, sf::Keyboard::Tab });
	KeyboardDetection::addKeyBinding("CTRL", { sf::Keyboard::LControl});
	KeyboardDetection::addKeyBinding("CTRL_W", { sf::Keyboard::LControl, sf::Keyboard::W });
	KeyboardDetection::addKeyBinding("CTRL_V", { sf::Keyboard::LControl, sf::Keyboard::V });
	srand(time(NULL));
}

int main() {

	setup();

	Window window1;
	window1.launch();

	return 0;
}