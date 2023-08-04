#pragma once

#ifndef GRAPHEDGE_HPP
#define GRAPHEDGE_HPP

#include <SFML/Graphics.hpp>
#include "Edge.hpp"

class GraphEdge: public Edge
{
public:
	GraphEdge(Node* _u, Node* _v);
	GraphEdge(Node* _u, Node* _v, int x);
	~GraphEdge() {};

	void update();

	Node *u, *v;
	int w = 0;
};

#endif // !GRAPHEDGE_HPP