#include "Input.hpp"
#include "Resources.hpp"
#include "Layout.hpp"
#include "Tools.hpp"
#include "Color.hpp"

void Input::create(sf::Vector2f pos, sf::Vector2f size, std::string label)
{
	labelButton.create(pos, size);
	labelButton.setText(label, Resources::Font::courier);
	labelButton.setRadius(5);

	labelButton.setState({ Layout::workplaceBackground, Layout::workplaceOutline, 1 }, 0);

	textbox.create(pos + sf::Vector2f(size.x + Layout::InputTable::spacing, 0), sf::Vector2f(Layout::InputTable::size.x - 3 * Layout::InputTable::spacing - size.x, size.y));
	textbox.setRadius(5);
	textbox.setState({ Layout::workplaceBackground, Layout::workplaceOutline, 1 }, 0);
	textbox.setState({ Color::LightGray, Layout::workplaceOutline, 1 }, 1);
	textbox.setState({ Layout::workplaceBackground, Layout::workplaceOutline, 1 }, 2);
}

void Input::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	textbox.handleEvent(window, event);
	labelButton.handleEvent(window, event);
	if (labelButton.justReleasedInside()) {
		newInput = 1;
	}
}

void Input::update()
{
	textbox.update();
	labelButton.update();
}

void Input::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(textbox);
	target.draw(labelButton);
}

std::string Input::getInput()
{
	newInput = 0;
	return textbox.getString();
}

std::string Input::getLabel()
{
	return labelButton.getLabel();
}
