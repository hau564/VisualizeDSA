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
		valueShapes[i].setFillColor(Color::LightGray);
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

void Node::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	MouseDetection::handleEvent(window, event);
}

void Node::update()
{
	if (isHolding()) {
		sf::Vector2f mousePos = Tools::Mouse::getPosition();
		if (holdingPosition.x >= 0) {
			sf::Vector2f delta = mousePos - holdingPosition;
			holdingPosition = mousePos;
			setPosition(getPosition() + delta);
		}
		holdingPosition = mousePos;
	}
	else holdingPosition = { -1, -1 };

	sf::Vector2f pos = getPosition();
	nodeShape.setPosition(pos);
	float spacing = Layout::DisplayComponent::Node::valueSpacing;
	float height = Layout::DisplayComponent::Node::height;
	float length = spacing;
	for (int i = 0; i < (int)valueShapes.size(); ++i) 
		length += valueShapes[i].getSize().x + spacing;

	float px = spacing;
	if (length < height) px += (height - length) / 2;
	for (int i = 0; i < (int)valueTexts.size(); ++i) {
		valueShapes[i].setPosition({pos.x + px, pos.y + spacing});
		if (!stringNode)
			valueTexts[i].setString(Tools::String::toString(values[i]));
		valueShapes[i].setSize({ std::max(valueTexts[i].getGlobalBounds().width + 2 * spacing, height - 2 * spacing), height - 2 * spacing });
		Tools::Text::middleAligning(valueTexts[i], valueShapes[i].getPosition(), valueShapes[i].getSize());
		px += valueShapes[i].getSize().x + spacing;
	}
	if (length < height) px += (height - length) / 2;

	nodeShape.setSize({std::max(px, height), height});
	MouseDetection::setSize(nodeShape.getSize());

	if (showingHeight) {
		heightText.setString(Tools::String::toString(this->height));
		heightText.setPosition(getPosition() + getSize());
	}
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(nodeShape, states);
	for (int i = 0; i < (int)valueTexts.size(); ++i) {
		if (valueTexts.size() > 1) target.draw(valueShapes[i], states);
		target.draw(valueTexts[i], states);
	}
	if (showingHeight)
		target.draw(heightText, states);
}

void Node::addValue(int x)
{
	values.push_back(x);
	create(values);
}

void Node::addValue(int x, int id)
{
	values.insert(values.begin() + id, x);
	create(values);
}

void Node::sortValue()
{
	std::sort(values.begin(), values.end());
	create(values);
}

void Node::setStringNode(int x)
{
	stringNode = x;
	if (!x) return;
	valueTexts.assign(1, sf::Text());
	valueShapes.assign(1, sf::RoundedRectangleShape());
	valueTexts[0].setFont(*Resources::Font::courier);

	std::string str = "";
	for (int i : values)
		str += std::string(1, i);

	valueTexts[0].setCharacterSize(Layout::DisplayComponent::Node::fontSize);
	valueTexts[0].setString(str);
	valueTexts[0].setFillColor(Color::Black);

	float spacing = Layout::DisplayComponent::Node::valueSpacing;
	float height = Layout::DisplayComponent::Node::height;
	valueShapes[0].setSize({ std::max(valueTexts[0].getGlobalBounds().width + 2 * spacing, height - 2 * spacing), height - 2 * spacing });

	update();
}

void Node::removeValue(int id)
{
	if (id >= values.size()) return;
	values.erase(values.begin() + id);
	create(values);
}

int Node::getValue(int id) const
{
	if (id >= values.size()) return 0;
	return values[id];
}

int Node::getValueCount() const
{
	return valueTexts.size();
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
	for (int i = 0; i < (int)valueTexts.size(); ++i) {
		valueTexts[i].setFillColor(color);
	}
}

sf::Color Node::getColor() const
{
	return color;
}

void Node::memorizePosition()
{
	memPos = getPosition();
	memCen = getCenter();
}

sf::Vector2f Node::getOldPosition() const
{
	return memPos;
}

sf::Vector2f Node::getOldCenter() const
{
	return memCen;
}

sf::RoundedRectangleShape& Node::Shape()
{
	return nodeShape;
}

bool Node::operator==(const Node& other) const
{
	return abs(getPosition().x - other.getPosition().x) <= 0.0001
		&& abs(getPosition().y - other.getPosition().y) <= 0.0001;
}

void Node::showHeight(int t, std::string s)
{
	showingHeight = t;
	if (t) {
		if (s == "") s = Tools::String::toString(height);
		heightText = sf::Text(s, *Resources::Font::courier, 35);
		heightText.setStyle(sf::Text::Bold);
		heightText.setPosition(getPosition() + getSize());
		heightText.setFillColor(Color::highlight);
	}
}
