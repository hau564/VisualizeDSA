#include "Tab.hpp"
#include "Layout.hpp"
#include "Color.hpp"

Tab::Tab(int _id) {
	create(_id);
}

void Tab::create(int _id)
{
	id = _id;
	Button::create(Layout::Tabbar::pos + sf::Vector2f(id * (Layout::Tab::size.x + 5), 0), Layout::Tab::size);
	Button::setRadius(Layout::Tab::radius);
	Button::setText("Tab 1", Layout::Font::arial);
	active = 1;
	Button::getStateId = [this](const Button* button) {
		return (active || (button->isHolding() && !xButton.isHolding())) ? 2 : (button->isFocusing() ? 1 : 0);
	};

	float xSize = Layout::Tab::size.y / 2;
	sf::Vector2f center = getPosition() + sf::Vector2f(getSize().x - Layout::Tab::size.y / 2, Layout::Tab::size.y / 2);
	xButton.create(center - sf::Vector2f(xSize / 2, xSize / 2), sf::Vector2f(xSize, xSize));
	xButton.setRadius(xSize / 2);
	xButton.setText("X", Layout::Font::arial);
	xButton.setState({ sf::Color::Transparent, Color::White, 0 }, 0);
	xButton.setState({ Color::GrayBG, Color::White, 0 }, 1);
	xButton.setState({ Color::DarkGray, Color::White, 0 }, 2);
}

void Tab::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	Button::handleEvent(window, event);
	xButton.handleEvent(window, event);
	if (xButton.justReleasedInside()) {
		removed = true;
	}
	else if (isHolding()) {
		active = 1;
		std::cout << "Active tab " << id << std::endl;
	}
}

void Tab::update()
{
	Button::update();
	xButton.update();
}

void Tab::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Button::draw(target, states);
	target.draw(xButton);
}

void Tab::updateId(int _id)
{
	id = _id;
	Button::setPosition(Layout::Tabbar::pos + sf::Vector2f(id * (Layout::Tab::size.x + 5), 0));
	xButton.setPosition(getPosition() + sf::Vector2f(getSize().x - Layout::Tab::size.y / 2, Layout::Tab::size.y / 2) - sf::Vector2f(Layout::Tab::size.y / 4, Layout::Tab::size.y / 4));
}

void Tab::deactive()
{
	active = false;
}

bool Tab::isRemove()
{
	return removed;
}

bool Tab::isActive()
{
	return active;
}
