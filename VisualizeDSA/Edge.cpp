#include "Edge.hpp"

#define PI 3.14159265359

Edge::Edge(sf::Vector2f _pos1, sf::Vector2f _pos2)
{
	create(_pos1, _pos2);
}

void Edge::create(sf::Vector2f _pos1, sf::Vector2f _pos2, sf::Color _color, float thickness, float dis)
{
	color = _color;
	pos1 = _pos1, pos2 = _pos2;
	float d = sqrt((pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y)) - dis;
	float angle = atan2(pos2.y - pos1.y, pos2.x - pos1.x);
	pos2 = { pos1.x + d * cos(angle), pos1.y + d * sin(angle) };

	line.setPosition(pos1);
	line.setSize({ d, thickness});
	line.setOrigin({ 0, thickness / 2 });
	line.setFillColor(color);
	line.setRotation(angle * 180 / PI);
	arrow.setRadius(thickness * 2);
	arrow.setPointCount(3);
	arrow.setOrigin({ thickness * 2, thickness * 2 });
	arrow.setPosition(pos2);
	arrow.setFillColor(color);
	arrow.setRotation(angle * 180 / PI + 90);
}

void Edge::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(line);
	if (direct) target.draw(arrow);
}

void Edge::setDirect(bool _direct)
{
	direct = _direct;
}

void Edge::setStart(sf::Vector2f pos)
{
	pos1 = pos;
	line.setPosition(pos1);
	line.setRotation(atan2(pos2.y - pos1.y, pos2.x - pos1.x) * 180 / PI);
	arrow.setPosition(pos2);
	arrow.setRotation(atan2(pos2.y - pos1.y, pos2.x - pos1.x) * 180 / PI + 90);
}

void Edge::setEnd(sf::Vector2f pos)
{
	pos2 = pos;
	line.setPosition(pos1);
	line.setRotation(atan2(pos2.y - pos1.y, pos2.x - pos1.x) * 180 / PI);
	arrow.setPosition(pos2);
	arrow.setRotation(atan2(pos2.y - pos1.y, pos2.x - pos1.x) * 180 / PI + 90);
}

void Edge::setColor(sf::Color _color)
{
	color = _color;
	line.setFillColor(color);
	arrow.setFillColor(color);
}

sf::Color Edge::getColor()
{
	return color;
}

bool Edge::operator==(const Edge& e) const
{
	return	abs(getStart().x - e.getStart().x) <= 0.0001
		&&	abs(getStart().y - e.getStart().y) <= 0.0001
		&&  abs(getEnd().x - e.getEnd().x) <= 0.0001
		&&  abs(getEnd().y - e.getEnd().y) <= 0.0001;
			
}

sf::Vector2f Edge::getStart() const
{
	return pos1;
}

sf::Vector2f Edge::getEnd() const
{
	return pos2;
}
