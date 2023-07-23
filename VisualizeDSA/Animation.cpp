#include "Animation.hpp"

float Animation::getFloat(float x, float y, float r)
{
	return x + (y - x) * r;
}

sf::Vector2f Animation::getVector2f(sf::Vector2f p1, sf::Vector2f p2, float r)
{
	return sf::Vector2f(getFloat(p1.x, p2.x, r), getFloat(p1.y, p2.y, r));
}

sf::Color Animation::getColor(sf::Color c1, sf::Color c2, float r)
{
	return sf::Color(getFloat(c1.r, c2.r, r), getFloat(c1.g, c2.g, r), getFloat(c1.b, c2.b, r));
}

Node Animation::getNode(Node n1, Node n2, float r)
{
	n1.setPosition(getVector2f(n1.getPosition(), n2.getPosition(), r));
	n1.setColor(getColor(n1.getColor(), n2.getColor(), r));
	n1.update();
	return n1;
}

Edge Animation::getEdge(Edge e1, Edge e2, float r)
{
	Edge e;
	e.create(getVector2f(e1.getStart(), e2.getStart(), r), getVector2f(e1.getEnd(), e2.getEnd(), r));
	e.setColor(getColor(e1.getColor(), e2.getColor(), r));
	return e;
}

Layer Animation::getLayer(Layer l1, Layer l2, float r)
{
	Layer layer;
	for (int i = 0; i < (int)l1.nodes.size(); i++)
		layer.nodes.push_back(getNode(l1.nodes[i], l2.nodes[i], r));
	for (int i = 0; i < (int)l1.edges.size() && i < (int)l2.edges.size(); i++)
		layer.edges.push_back(getEdge(l1.edges[i], l2.edges[i], r));
	return layer;
}
