#include "Tab.hpp"
#include "Layout.hpp"

Tab::Tab(int _id) {
	id = _id;
	Button::create(Layout::Tabbar::pos + sf::Vector2f(id * Layout::Tab::size.x, 0), Layout::Tab::size);
	Button::setRadius(Layout::Tab::radius);
	active = 1;
}

void Tab::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	Button::handleEvent(window, event);
}

void Tab::update()
{
	Button::update();
}

void Tab::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!active) return;
	Button::draw(target, states);
}

bool Tab::isActive()
{
	return active;
}
