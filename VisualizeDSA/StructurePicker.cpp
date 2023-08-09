#include "StructurePicker.hpp"
#include "Layout.hpp"
#include "Color.hpp"

void StructurePicker::create()
{
	buttons.assign(n, Button());
	sprites.assign(n, sf::Sprite());
	float buttonRadius = 7;
	float lengtButtonsBar = (n + n - 1) * 2 * buttonRadius;
	float buttonY = 100;
	float buttonX = Layout::Window::width / 2 - lengtButtonsBar / 2;

	for (int i = 0; i < n; ++i) {
		buttons[i].create({buttonX + i * (4 * buttonRadius), buttonY}, {2 * buttonRadius, 2 * buttonRadius});
		buttons[i].setRadius(buttonRadius);
		buttons[i].setState({ sf::Color::White, sf::Color::Black, 0.3f }, 0);
		buttons[i].setState({Color::GrayBG, sf::Color::White, 0}, 1);
		buttons[i].setState({Color::DarkGray, sf::Color::White, 0}, 2);

		sprites[i].setTexture(Resources::Textures::getTexture(names[i]));
		sprites[i].setPosition(Layout::Tabbar::size + sf::Vector2f(0, Layout::Tabbar::size.y));
		sf::Vector2f size = (sf::Vector2f)Resources::Textures::getTexture(names[i]).getSize();
		sprites[i].setScale(Layout::Window::width / size.x , (Layout::Window::height - Layout::Tabbar::size.y - Layout::Tabbar::pos.y) / size.y);
	}
	buttons[focusId].addGetStateId([](const Button* button) { return 2; });

	sf::Vector2f size = { 200, 50 };
	sf::Vector2f center = { Layout::Window::width / 2, Layout::Window::height / 2 + 430};
	start.create({ center.x - size.x / 2, center.y - size.y / 2 }, size);
	start.setText("Start", Resources::Font::courier);
	start.setStates(Layout::Button::states2);
	start.setRadius(10);

	float spacing = 20;
	minHeap.create({ center.x - size.x - spacing , center.y - size.y / 2 }, size);
	minHeap.setText("MinHeap", Resources::Font::courier);
	minHeap.setStates(Layout::Button::states2);
	minHeap.setRadius(10);
	maxHeap.create({ center.x + spacing , center.y - size.y / 2 }, size);
	maxHeap.setText("MaxHeap", Resources::Font::courier);
	maxHeap.setStates(Layout::Button::states2);
	maxHeap.setRadius(10);

	workPlace.setPosition({ 0, Layout::Tabbar::size.y + Layout::Tabbar::pos.y });
	workPlace.setSize({ 1.f * Layout::Window::width, 1.f * Layout::Window::height - Layout::Tabbar::size.y });
}

void StructurePicker::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	int prevFocus = focusId;
	for (int i = 0; i < (int)buttons.size(); ++i) {
		buttons[i].handleEvent(window, event);
		if (buttons[i].justReleasedInside()) focusId = i;
	}
	workPlace.handleEvent(window, event);
	if (workPlace.isFocusing() && event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
		if (event.mouseWheelScroll.delta > 0) {
			focusId = (focusId - 1 + n) % n;
		}
		else {
			focusId = (focusId + 1) % n;
		}
	}
	if (focusId != prevFocus)
	for (int i = 0; i < (int)buttons.size(); ++i) {
		if (i == focusId) buttons[i].addGetStateId([](const Button* button) { return 2; });
		else buttons[i].removeGetStateId(0);
	}
	if (focusId != 3)
		start.handleEvent(window, event);
	else {
		minHeap.handleEvent(window, event);
		maxHeap.handleEvent(window, event);
	}
	if (focusId == 3) {
		if (minHeap.justReleasedInside()) {
			stringPicked = "MinHeap";
		}
		else if (maxHeap.justReleasedInside()) {
			stringPicked = "MaxHeap";
		}
	}
	else {
		if (start.justReleasedInside()) {
			stringPicked = names[focusId];
		}
	}
}

void StructurePicker::update()
{
	for (int i = 0; i < (int)buttons.size(); ++i) {
		buttons[i].update();
	}
	workPlace.update();
	if (focusId == 3) {
		minHeap.update();
		maxHeap.update();
	}
	else start.update();
}

void StructurePicker::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprites[focusId]);
	for (int i = 0; i < (int)buttons.size(); ++i) {
		target.draw(buttons[i]);
	}
	if (focusId == 3) {
		target.draw(minHeap);
		target.draw(maxHeap);
	}
	else
		target.draw(start);
}

std::string StructurePicker::getPicked() const
{
	return stringPicked;
}
