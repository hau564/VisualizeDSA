#include "GraphEdge.hpp"
#include "Tools.hpp"
#include <iostream>

GraphEdge::GraphEdge(Node* _u, Node* _v)
{
	u = _u;
	v = _v;
	create(u->getCenter(), v->getCenter());
}

GraphEdge::GraphEdge(Node* _u, Node* _v, int x)
{
	u = _u;
	v = _v;
	w = x;
	create(u->getCenter(), v->getCenter());
	setText(Tools::String::toString(w));
}

void GraphEdge::update()
{
	create(u->getCenter(), v->getCenter(), getColor());
	setText(Tools::String::toString(w));
}
