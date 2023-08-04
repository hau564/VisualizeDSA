#pragma once

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include "Visualizer.hpp"

class Graph
{
public:
	void setup(Visualizer* visualizer);
	void visualize();

private:
	void createGraph();
	void createNodes(std::vector<int> _n);
	void createEdges(std::vector<std::pair<std::pair<int, int>, int>> _n);

	void buildAdj();

	void connectedComponent();
	void dijkstra(int s);
	void kruskal();

	Visualizer* visualizer;
	std::vector<Node*> nodes;
	std::vector<GraphEdge*> edges;
	std::map<int, int> pos;
	std::map<int, std::vector<int>> adj;
	std::vector<int> coreNodes;
	std::vector<std::pair<std::pair<int, int>, int>> coreEdges;
};

#endif // !GRAPH_HPP