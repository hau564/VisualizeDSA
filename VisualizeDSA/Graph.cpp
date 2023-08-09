#include "Graph.hpp"
#include "Tools.hpp"
#include <iostream>
#include <queue>

void Graph::setup(Visualizer* _visualizer)
{
	visualizer = _visualizer;
	visualizer->setTextboxes({ "Nodes", "Edges", "CC", "Dijkstra", "Kruskal" });
	/*visualizer->addTextbox("Nodes");
	visualizer->addTextbox("Edges");
	visualizer->addTextbox("CC");
	visualizer->addTextbox("Dijkstra");
	visualizer->addTextbox("Kruskal");*/
}

void Graph::visualize()
{
	if (!visualizer->newInput) return;
	std::string label, input;
	visualizer->getInput(label, input);
	if (label == "Nodes") {
		if (!Tools::String::isVectorInt(input)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
		createNodes(Tools::String::toVectorInt(input));
	}
	else if (label == "Edges") {
		std::vector<std::pair<std::pair<int, int>, int>> edges;
		if (!Tools::String::toVectorEdges(input, edges)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
		createEdges(edges);
	}
	else if (label == "CC") {
		connectedComponent();
	}
	else if (label == "Dijkstra") {
		if (!Tools::String::isInt(input)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
		dijkstra(Tools::String::toInt(input));
	}
	else if (label == "Kruskal") {
		kruskal();
	}
}

void Graph::createGraph(int rearrange)
{
	for (Node* node : nodes) {
		delete node;
	}
	for (GraphEdge* edge : edges) {
		delete edge;
	}
	edges.clear();
	nodes.clear();
	pos.clear();
	coreNodes = originalNodes;
	
	for (int i = 0; i < coreNodes.size(); i++) {
		nodes.push_back(new Node({ coreNodes[i] }));
		pos[coreNodes[i]] = i;
	}

	for (std::pair<std::pair<int, int>, int> edge : coreEdges) {
		if (pos.find(edge.first.first) == pos.end()) {
			nodes.push_back(new Node({ edge.first.first }));
			coreNodes.push_back(edge.first.first);
			pos[edge.first.first] = nodes.size() - 1;
		}
		if (pos.find(edge.first.second) == pos.end()) {
			nodes.push_back(new Node({ edge.first.second }));
			coreNodes.push_back(edge.first.second);
			pos[edge.first.second] = nodes.size() - 1;
		}
		edges.push_back(new GraphEdge(nodes[pos[edge.first.first]], nodes[pos[edge.first.second]], edge.second));
	}
	visualizer->setGraph(nodes, edges);
}

void Graph::createNodes(std::vector<int> _coreNodes)
{
	coreNodes = originalNodes = _coreNodes;
	createGraph(1);
}

void Graph::createEdges(std::vector<std::pair<std::pair<int, int>, int>> _coreEdges)
{
	coreEdges = _coreEdges;
	createGraph();
}

void Graph::buildAdj()
{
	adj.clear();
	for (int i = 0; i < (int)coreEdges.size(); ++i) {
		adj[coreEdges[i].first.first].push_back(i);
		adj[coreEdges[i].first.second].push_back(i);
	}
}

void Graph::connectedComponent()
{
	if (nodes.empty()) return;
	std::cout << "Connected Component" << std::endl;
	buildAdj();
	/*std::map<std::pair<std::pair<int, int>, int>, GraphEdge*> linkEdges;
	for (GraphEdge* edge : edges) {
		linkEdges.emplace(std::make_pair(std::make_pair(edge->u->getValue(), edge->v->getValue()), edge));
	}*/
	std::map<int, int> visited;
	for (int u : coreNodes) {
		if (visited.find(u) != visited.end()) continue;
		sf::Color color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
		std::queue<int> q;
		q.push(u);
		visited[u] = u;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			nodes[pos[u]]->setColor(color);
			for (int i : adj[u]) {
				int v = coreEdges[i].first.first ^ coreEdges[i].first.second ^ u;
				if (visited.find(v) == visited.end()) {
					q.push(v);
					visited[v] = u;
				}
			}
		}
	}
}

void Graph::dijkstra(int s)
{
	std::cout << "Dijkstra " << s << std::endl;
	buildAdj();
	std::map<int, int> f;
	f[s] = 0;
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> h;
	h.push({ f[s], s });
	while (!h.empty()) {
		int u = h.top().second, s = h.top().first;
		h.pop();
		if (f[u] != s) continue;
		for (int i : adj[u]) {
			int v = coreEdges[i].first.first ^ coreEdges[i].first.second ^ u;
			if (f.find(v) == f.end() || f[v] > f[u] + coreEdges[i].second) {
				h.push({ f[v] = f[u] + coreEdges[i].second, v });
			}
		}
	}

	for (Node* node : nodes) {
		if (f.find(node->getValue()) == f.end()) continue;
		node->height = f[node->getValue()];
		node->showHeight(1);
	}
}

void Graph::kruskal()
{
	std::cout << "Kruskal" << std::endl;
	buildAdj();
	sort(edges.begin(), edges.end(), [](GraphEdge* a, GraphEdge* b) {
		return a->w < b->w;
	});

	if (nodes.empty() && edges.empty()) return;

	std::map<int, int> f;
	for (auto edge : coreEdges) {
		f[edge.first.first] = f[edge.first.second] = -1;
	}
	std::function<int(int)> Find = [&](int x) mutable {
		return f[x] < 0 ? x : f[x] = Find(f[x]);
	};
	std::function<bool(int, int)> merge = [&](int x, int y) mutable {
		if ((x = Find(x)) == (y = Find(y))) return false;
		if (f[x] > f[y]) std::swap(x, y);
		f[x] += f[y];
		f[y] = x;
		return true;
	};
	for (GraphEdge* edge : edges) {
		if (merge(edge->u->getValue(), edge->v->getValue())) {
			((Edge*)edge)->setColor(Color::highlight);
		}
	}
}
