#include "VisualizeDSA.hpp"


void setup() {
	Resources::Font::load();
	Resources::Textures::load();
	KeyboardDetection::addKeyBinding("CTRL_TAB", { sf::Keyboard::LControl, sf::Keyboard::Tab });
	KeyboardDetection::addKeyBinding("CTRL_W", { sf::Keyboard::LControl, sf::Keyboard::W });
}

int main() {

	setup();

	Window window1;
	window1.launch();

	return 0;
}