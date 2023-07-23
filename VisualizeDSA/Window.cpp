#include "Window.hpp"
#include "Layout.hpp"
#include "KeyboardDetection.hpp"
#include "Textbox.hpp"
#include "Display.hpp"
#include "Layer.hpp"
#include "ControlBox.hpp"
#include "Tools.hpp"

void Window::setup()
{
	tabs.push_back(Tab());
	tabs.back().create(0);
	newTab.create(Layout::Tabbar::pos + sf::Vector2f(Layout::Tab::size.x + 5, 2), sf::Vector2f(Layout::Tab::size.y - 4, Layout::Tab::size.y - 4));
	newTab.setText("+", Resources::Font::arial);
	newTab.setRadius(Layout::Tab::size.y / 2);
}

void Window::addTab()
{
	tabs.push_back(Tab());
	tabs.back().create(tabs.size() - 1);
}

void Window::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	static int activeId = 0;
	newTab.handleEvent(window, event);
	if (newTab.justReleasedInside()) {
		addTab();
		activeId = tabs.size() - 1;
	}

	KeyboardDetection::handleEvent(window, event);
	for (int i = 0; i < tabs.size(); ++i) {
		tabs[i].updateId(i);
		tabs[i].handleEvent(window, event);
		if (tabs[i].isRemove()) {
			tabs.erase(tabs.begin() + i);
			--i;
		}
		if (tabs[i].isHolding()) {
			activeId = i;
		}
	}
	if (activeId >= tabs.size()) activeId = tabs.size() - 1;
	if (KeyboardDetection::isKeyBindingPressed("CTRL_TAB")) 
		activeId = (activeId + 1) % tabs.size();
	for (int i = 0; i < tabs.size(); ++i)
		if (i != activeId) 
			tabs[i].deactive();
		else tabs[i].activate();
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
	sf::RenderWindow window(sf::VideoMode(Layout::Window::width, Layout::Window::height), "Data structures & Algorithm Visualizer", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	setup();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); break; }
			handleEvent(window, event);
		}

		update();

		window.clear(Layout::Window::backgroundColor);
		
		draw(window);
		
		window.display();
	}

	while (!tabs.empty()) tabs.pop_back();
}

int Window::getTabCount()
{
	return tabs.size();
}

sf::Vector2f Window::getNewSlot()
{
	return Layout::Tabbar::pos + sf::Vector2f(getTabCount() * Layout::Tab::size.x, 0);
}
