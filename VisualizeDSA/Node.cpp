#include "Node.hpp"
#include "Layout.hpp"
#include "Resources.hpp"
#include "Tools.hpp"
#include "Color.hpp"

Node::Node(sf::Vector2f _pos, std::vector<int> values)
{
	setPosition(_pos);
	create(values);
}

void Node::create(std::vector<int> _values)
{
	values = _values;	
	float px = 0, py = 0, height = Layout::DisplayComponent::Node::height, spacing = Layout::DisplayComponent::Node::valueSpacing;
	int n = values.size();
	valueTexts.assign(n, sf::Text());
	valueShapes.assign(n, sf::RoundedRectangleShape());
	for (int i = 0; i < (int)values.size(); ++i) {
		valueTexts[i].setFont(*Resources::Font::courier);
		valueTexts[i].setString(Tools::String::toString(values[i]));
		valueTexts[i].setCharacterSize(Layout::DisplayComponent::Node::fontSize);
		valueTexts[i].setFillColor(Color::Black);

		//valueShapes[i].setSize({valueTexts[i].getGlobalBounds().width, valueTexts[i].getGlobalBounds().height + 10});
		valueShapes[i].setSize({std::max(valueTexts[i].getGlobalBounds().width + 2 * spacing, height - 2 * spacing), height - 2 * spacing});
		valueShapes[i].setFillColor(Color::GrayBG);
		valueShapes[i].setCornersRadius(valueShapes[i].getSize().y / 2.5);
		valueShapes[i].setCornerPointCount(50);
	}
	nodeShape.setOutlineThickness(3);
	nodeShape.setOutlineColor(Color::Black);
	color = Color::Black;
	nodeShape.setCornersRadius(Layout::DisplayComponent::Node::height / 2);
	nodeShape.setCornerPointCount(50);
	update();
}

void Node::update()
{
	sf::Vector2f pos = getPosition();
	nodeShape.setPosition(pos);
	float spacing = Layout::DisplayComponent::Node::valueSpacing;
	float height = Layout::DisplayComponent::Node::height;
	float length = spacing;
	for (int i = 0; i < (int)values.size(); ++i) 
		length += valueShapes[i].getSize().x + spacing;

	float px = spacing;
	if (length < height) px += (height - length) / 2;
	for (int i = 0; i < (int)values.size(); ++i) {
		valueShapes[i].setPosition({pos.x + px, pos.y + spacing});
		Tools::Text::middleAligning(valueTexts[i], valueShapes[i].getPosition(), valueShapes[i].getSize());
		px += valueShapes[i].getSize().x + spacing;
	}
	if (length < height) px += (height - length) / 2;

	nodeShape.setSize({std::max(px, height), height});
	MouseDetection::setSize(nodeShape.getSize());
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(nodeShape, states);
	for (int i = 0; i < (int)values.size(); ++i) {
		if (values.size() > 1) target.draw(valueShapes[i], states);
		target.draw(valueTexts[i], states);
	}
}

int Node::getValue(int id) const
{
	return values[id];
}

std::vector<int> Node::getValues() const
{
	return values;
}

int& Node::Value(int id)
{
	return values[id];
}

void Node::setColor(sf::Color _color)
{
	color = _color;
	nodeShape.setOutlineColor(color);
}

sf::Color Node::getColor() const
{
	return color;
}

void Node::memorizePosition()
{
	memPos = getPosition();
}

sf::Vector2f Node::getOldPosition() const
{
	return memPos;
}

sf::Vector2f Node::getOldCenter() const
{
	return memPos + sf::Vector2f(getSize().x / 2, getSize().y / 2);
}

bool Node::operator==(const Node& other) const
{
	return abs(getPosition().x - other.getPosition().x) <= 0.0001
		&& abs(getPosition().y - other.getPosition().y) <= 0.0001;
}
