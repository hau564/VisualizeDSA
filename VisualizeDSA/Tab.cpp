#include "Tab.hpp"
#include "Layout.hpp"
#include "Color.hpp"
#include "Tools.hpp"
#include "KeyboardDetection.hpp"
Tab::Tab(int _id) {
	create(_id);
}

void Tab::create(int _id)
{
	id = _id;
	Button::create(Layout::Tabbar::pos + sf::Vector2f(id * (Layout::Tab::size.x + 5), 0), Layout::Tab::size);
	Button::setRadius(Layout::Tab::radius);
	Button::setText("Tab " + Tools::String::toString(id + 1), Resources::Font::arial);
	active = 1;
	cover.setSize(getSize());

	float xSize = Layout::Tab::size.y / 2;
	sf::Vector2f center = getPosition() + sf::Vector2f(getSize().x - Layout::Tab::size.y / 2, Layout::Tab::size.y / 2);
	xButton.create(center - sf::Vector2f(xSize / 2, xSize / 2), sf::Vector2f(xSize, xSize));
	xButton.setRadius(xSize / 2);
	xButton.setText("X", Resources::Font::arial);
	xButton.setState({ sf::Color::Transparent, Color::White, 0 }, 0);
	xButton.setState({ Color::GrayBG, Color::White, 0 }, 1);
	xButton.setState({ Color::DarkGray, Color::White, 0 }, 2);

	structurePicker.create();
	workingArea.setPosition({ 0, Layout::Tabbar::size.y + Layout::Tabbar::pos.y });
	workingArea.setSize({ 1.f * Layout::Window::width, 1.f * Layout::Window::height - Layout::Tabbar::size.y});
	workingArea.setFillColor(Color::White);
}

void Tab::updateId(int _id)
{
	id = _id;
	Button::setPosition(Layout::Tabbar::pos + sf::Vector2f(id * (Layout::Tab::size.x + 5), 0));
	if (structurePicker.getPicked() == "#")
		Button::setText("Tab " + Tools::String::toString(id + 1), Resources::Font::arial);
	xButton.setPosition(getPosition() + sf::Vector2f(getSize().x - Layout::Tab::size.y / 2, Layout::Tab::size.y / 2) - sf::Vector2f(Layout::Tab::size.y / 4, Layout::Tab::size.y / 4));
}

void Tab::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	Button::handleEvent(window, event);
	xButton.handleEvent(window, event);
	if (xButton.justReleasedInside() || KeyboardDetection::isKeyBindingPressed("CTRL_W")) {
		removed = true;
	}
	else if (isHolding()) {
		active = 1;
	}

	if (!active) return;
		
	if (structurePicker.getPicked() != "#") {
		structureRunner.handleEvent(window, event);
		return;
	}
	if (structurePicker.getPicked() == "#")
		structurePicker.handleEvent(window, event);
	if (structurePicker.getPicked() != "#") {
		Button::setText(structurePicker.getPicked(), Resources::Font::arial);
		structureRunner.create(structurePicker.getPicked());
	}
}

void Tab::update()
{
	Button::update();
	xButton.update();
	cover.setPosition(getPosition() + sf::Vector2f(0, Layout::Tab::size.y / 2));
	if (active) {
		if (!added) {
			Button::addGetStateId(
				[](const Button* button) {
					return 2;
				}
			);
		}
		added = 1;

		if (structurePicker.getPicked() != "#") {
			structureRunner.update();
			return;
		}
		else {
			structurePicker.update();
		}
	}
	else Button::removeGetStateId(0), added = 0;
	if (!active) return;
}

void Tab::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (active) target.draw(cover);
	Button::draw(target, states);
	target.draw(xButton);
	if (!active) return;

	target.draw(workingArea);
	if (structurePicker.getPicked() != "#") {
		target.draw(structureRunner);
	}
	else { 
		target.draw(structurePicker);
	}
}

void Tab::activate()
{
	active = true;
}

void Tab::deactive()
{
	active = false;
}

bool Tab::isRemove()
{
	return removed;
}

bool Tab::isActive() const
{
	return active;
}
