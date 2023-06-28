#include "Window.hpp"
#include "Layout.hpp"
#include "KeyboardDetection.hpp"
#include "Textbox.hpp"


void Window::setup()
{
	tabs.push_back(Tab());
	tabs.back().create(0);
	newTab.create(Layout::Tabbar::pos + sf::Vector2f(Layout::Tab::size.x + 5, 2), sf::Vector2f(Layout::Tab::size.y - 4, Layout::Tab::size.y - 4));
	newTab.setText("+", Layout::Font::arial);
	newTab.setRadius(Layout::Tab::size.y / 2);
}

void Window::addTab()
{
	tabs.push_back(Tab());
	tabs.back().create(tabs.size() - 1);
	std::cout << "Added tab " << tabs.size() << std::endl;
}

void Window::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	newTab.handleEvent(window, event);
	if (newTab.justReleasedInside()) addTab();

	static int activeId = 0;
	KeyboardDetection::handleEvent(window, event);
	for (int i = 0; i < tabs.size(); ++i) {
		tabs[i].updateId(i);
		tabs[i].handleEvent(window, event);
		if (tabs[i].isRemove()) {
			tabs.erase(tabs.begin() + i);
			std::cout << "Removed tab " << i << std::endl;
			--i;
		}
		if (tabs[i].isHolding()) {
			activeId = i;
		}
	}
	//std::cout << "Active " << activeId << std::endl;
	for (int i = 0; i < tabs.size(); ++i)
		if (i != activeId) 
			tabs[i].deactive();

	if (tabs.empty()) addTab();
}

void Window::update()
{
	KeyboardDetection::update();
	for (Tab& tab : tabs)
		tab.update();
	newTab.update();
	newTab.setPosition(tabs.back().getPosition() + sf::Vector2f(Layout::Tab::size.x + 5, 0));
}

void Window::draw(sf::RenderWindow& window)
{
	for (Tab& tab : tabs)
		window.draw(tab);
	window.draw(newTab);
}

void Window::launch()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 5.0;
	sf::RenderWindow window(sf::VideoMode(Layout::Screen::width, Layout::Screen::height), "Data structures & Algorithm Visualizer", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	setup();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }

			handleEvent(window, event);
		}

		update();

		window.clear(Layout::Screen::backgroundColor);

		draw(window);

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
