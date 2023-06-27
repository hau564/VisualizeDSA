#include "Window.hpp"
#include "Layout.hpp"
#include "KeyboardDetection.hpp"

void Window::launch()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 5.0;
	sf::RenderWindow window(sf::VideoMode(Layout::Screen::width, Layout::Screen::height), "Data structures & Algorithm Visualizer", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	tabs.push_back(Tab(0));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }

			KeyboardDetection::handleEvent(window, event);
			for (Tab& tab : tabs) {
				tab.handleEvent(window, event);
			}
		}

		KeyboardDetection::update();
		for (Tab& tab : tabs) 
			tab.update();

		window.clear(Layout::Screen::backgroundColor);

		for (Tab& tab : tabs) 
			tab.draw(window, sf::RenderStates::Default);

		window.display();
	}
}

int Window::getTabCount()
{
	return tabs.size();
}

sf::Vector2f Window::getNewSlot()
{
	return Layout::Tabbar::pos + sf::Vector2f(getTabCount() * Layout::Tab::size.x, 0);
}
