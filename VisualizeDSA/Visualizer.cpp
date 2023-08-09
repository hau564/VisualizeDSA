#include "Visualizer.hpp"
#include "Layout.hpp"
#include <queue>
#include <set>
#include "Animation.hpp"

void Visualizer::setup()
{
	Display::setup();
	InputTable::setup();
}

void Visualizer::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	Display::handleEvent(window, event);	
	InputTable::handleEvent(window, event);
	if (graphMode) {
		for (Node *node : nodes) node->handleEvent(window, event);
	}
}

void Visualizer::update()
{
	Display::update();
	InputTable::update();
	if (graphMode) {
		for (Node* node : nodes) node->update();
		for (GraphEdge* edge : edges) edge->update();
	}
}

void Visualizer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Display::draw(target, states);
	if (!Display::isPlaying()) {
		if (graphMode) {
			for (GraphEdge* edge : edges) {
				target.draw(*edge, states);
			}
			for (Node* node : nodes) {
				target.draw(*node, states);
			}
		}
	}
	InputTable::draw(target, states);
}

void Visualizer::setGraph(std::vector<Node*> _nodes, std::vector<GraphEdge*> _edges)
{
	graphMode = 1;
	nodes = _nodes;
	edges = _edges;
	float y = 0;
	for (Node* node : nodes) {
		node->setPosition({ 1.f * (rand() % 1000 + 100), 1.f * (rand() % 700 + 100) });
		node->update();
	}
	for (GraphEdge* edge : edges) edge->update();
}

void Visualizer::dfsLayout(TreeNode* root, sf::Vector2f &pos, float horizontalSpacing, float verticalSpacing) {
	if (root == nullptr) return;
	int cntChild = root->getValueCount() + 1;

	if (root->stringNode) {
		int cntReal = root->getRealChildCount();
		int cnt = 0;
		cntChild = 0;
		while (cnt * 2 < cntReal) cnt += (root->Child(cntChild++) != nullptr);
		cntChild *= 2;
	}

	TreeNode *lastChild = nullptr;
	for (int i = 0; i < (cntChild + 1) / 2; ++i) {
		pos.y += verticalSpacing;
		dfsLayout(root->Child(i), pos, horizontalSpacing, verticalSpacing);
		pos.y -= verticalSpacing;
		if (root->Child(i) != nullptr) lastChild = root->Child(i);
	}
	root->memorizePosition();
	if (root->getRealChildCount() == 1 && root->stringNode) {
		sf::Vector2f _pos = lastChild->getPosition() + sf::Vector2f(lastChild->getSize().x - root->getSize().x, 0);
		_pos.y -= verticalSpacing;
		root->setPosition(_pos);
	}
	else {
		root->setPosition(pos);
		pos.x += horizontalSpacing + root->getSize().x;
	}
	for (int i = (cntChild + 1) / 2; i < (root->stringNode ? 26 : cntChild); ++i) {
		pos.y += verticalSpacing;
		dfsLayout(root->Child(i), pos, horizontalSpacing, verticalSpacing);
		pos.y -= verticalSpacing;
	}
}

void Visualizer::layoutTree(TreeNode* root, sf::Vector2f _pos)
{
	treePos = _pos;
	sf::Vector2f pos = _pos;
	dfsLayout(root, pos, Layout::DisplayComponent::Tree::horizontalSpacing, Layout::DisplayComponent::Tree::verticalSpacing);
}

void dfsSkip(TreeNode* root, TreeNode* node, int id, sf::Vector2f& pos, float horizontalSpacing, float verticalSpacing) {
	if (root == nullptr) return;
	std::vector<TreeNode*> childs;
	for (int i = 0; i < root->getValueCount() + 1; ++i) childs.push_back(root->Child(i));
	if (root == node) {
		childs.clear();
		for (int i = 0; i < id; ++i) {
			childs.push_back(root->Child(i));
		}
		for (TreeNode* node : root->Child(id)->childs) {
			childs.push_back(node);
		}
		for (int i = id + 1; i < root->getValueCount() + 1; ++i) {
			childs.push_back(root->Child(i));
		}
	}

	int cntChild = childs.size();
	for (int i = 0; i < (cntChild + 1) / 2; ++i) {
		pos.y += verticalSpacing;
		dfsSkip(childs[i], node, id, pos, horizontalSpacing, verticalSpacing);
		pos.y -= verticalSpacing;
	}
	root->memorizePosition();
	root->setPosition(pos);

	if (root == node) {
		root->Child(id)->memorizePosition();
		root->Child(id)->setPosition(root->getCenter() - root->Child(id)->getSize() / 2.f);
	}

	pos.x += horizontalSpacing + root->getSize().x;
	for (int i = (cntChild + 1) / 2; i < cntChild; ++i) {
		pos.y += verticalSpacing;
		dfsSkip(childs[i], node, id, pos, horizontalSpacing, verticalSpacing);
		pos.y -= verticalSpacing;
	}
}

void Visualizer::layoutTreeSkipEdge(TreeNode* root, TreeNode* node, int childId, sf::Vector2f _pos)
{
	sf::Vector2f pos = _pos;
	dfsSkip(root, node, childId, pos, Layout::DisplayComponent::Tree::horizontalSpacing, Layout::DisplayComponent::Tree::verticalSpacing);
}

void Visualizer::newStep(std::string s)
{
	if (s == "") s = prev;
	else prev = s;
	index = layers.size();
	for (int i = 0; i < fps; ++i) {
		if (!i || i == fps / 2 - 1 || i == fps / 2 || i == fps - 1)
			addLayer(Layer(), 1.f / fps, s);
		else 
			addVirtualLayer(1.f / fps, s);
	}
}

void Visualizer::newStep(TreeNode* root, std::string s)
{
	newStep(s);
	addTree(root);
}

void Visualizer::duplicateState(std::string s)
{
	if (s == "") s = prev;
	else prev = s;
	index = layers.size();
	if (index)
		for (int i = 0; i < fps; ++i) {
			if (!i || i == fps / 2 - 1 || i == fps / 2 || i == fps - 1)
				addLayer(layers[index - 1], 1.f / fps, s);
			else
				addVirtualLayer(1.f / fps, s);
		}
	else
		newStep();
}

void Visualizer::addTree(TreeNode* root)
{
	for (int i : {0, fps / 2 - 1, fps / 2, fps - 1})
		layers[index + i].addTree(root);
}

void Visualizer::moveEdge(Node* u, Node* v, Node* uu, Node* vv)
{
	moveEdge(u->getCenter(), v->getCenter(), uu->getCenter(), vv->getCenter());
}

void Visualizer::moveEdge(sf::Vector2f u, sf::Vector2f v, sf::Vector2f uu, sf::Vector2f vv)
{
	int eid = -1;
	for (int i = 0; i < (int)layers[index].edges.size(); ++i) {
		if (layers[index].edges[i] == Edge(u, v)) {
			eid = i;
			break;
		}
	}
	if (eid < 0) {
		eid = layers[index].edges.size();
		u = v = uu;
		for (int i : {0, fps / 2 - 1, fps / 2, fps - 1}) {
			layers[i + index].edges.push_back(Edge(u, u));
		}
	}
	for (int i : {0, fps / 2 - 1, fps / 2, fps - 1}) {
		layers[i + index].edges[eid].create(Animation::getVector2f(u, uu, (float)(i + 1) / fps), Animation::getVector2f(v, vv, (float)(i + 1) / fps), layers[i + index].edges[eid].getColor());
	}
}

void Visualizer::removeEdge(sf::Vector2f u, sf::Vector2f v)
{
	int eid = -1;
	for (int i = 0; i < (int)layers[index].edges.size(); ++i) {
		if (layers[index].edges[i] == Edge(u, v)) {
			eid = i;
			break;
		}
	}
	if (eid < 0) return;
	sf::Color color = layers[index].edges[eid].getColor();
	for (int i : {0, fps / 2 - 1, fps / 2, fps - 1}) {
		layers[i + index].edges[eid].create(u, v, Animation::getColor(color, Layout::workplaceBackground, std::min(1.f, 2.f * (i + 1) / fps)));
	}
	layers[fps / 2 + index].edges[eid].setStart({ -100, -100 });
	layers[fps / 2 + index].edges[eid].setEnd({ -100, -100 });
	layers[fps - 1 + index].edges[eid].setStart({ -100, -100 });
	layers[fps - 1 + index].edges[eid].setEnd({ -100, -100 });
}

void Visualizer::removeEdgeFromParent(Node* v)
{
	removeEdgeFromParent(v->getCenter());
}

bool operator == (sf::Vector2f pos1, sf::Vector2f pos2) {
	return abs(pos1.x - pos2.x) <= 1
		&& abs(pos1.y - pos2.y) <= 1;
}

void Visualizer::removeEdgeFromParent(sf::Vector2f v)
{
	for (Edge edge : layers[index].edges) {
		if (edge.getEnd() == v) {
			removeEdge(edge.getStart(), edge.getEnd());
			return;
		}
	}
}

void Visualizer::moveNode(sf::Vector2f pos1, sf::Vector2f pos2, std::vector<int> _values)
{
	int eid = -1;
	for (int i = 0; i < (int)layers[index].nodes.size(); ++i) {
		if (layers[index].nodes[i] == Node(pos1)) {
			eid = i;
			break;
		}
	}
	if (eid < 0) {
		eid = layers[index].nodes.size();
		for (int i : {0, fps / 2 - 1}) {
			layers[i + index].nodes.push_back(Node({ -1000, -1000 }, _values));
		}
		sf::Color color = Layout::workplaceOutline;
		for (int i : {fps / 2, fps - 1}) {
			layers[i + index].nodes.push_back(Node(pos2, _values));
			layers[i + index].nodes.back().setColor(Animation::getColor(Layout::workplaceBackground, color, 2.f * (i - fps / 2.f) / fps));
		}
		return;
	}
	for (int i : {0, fps / 2 - 1, fps / 2, fps - 1}) {
		layers[i + index].nodes[eid].setPosition(Animation::getVector2f(pos1, pos2, (float)(i + 1) / fps));
		layers[i + index].nodes[eid].update();
	}
}

void Visualizer::moveNode(sf::Vector2f pos1, sf::Vector2f pos2, Node node)
{
	int eid = -1;
	for (int i = 0; i < (int)layers[index].nodes.size(); ++i) {
		if (layers[index].nodes[i] == Node(pos1)) {
			eid = i;
			break;
		}
	}
	if (eid < 0) {
		eid = layers[index].nodes.size();
		for (int i : {0, fps / 2 - 1}) {
			layers[i + index].nodes.push_back(node);
			layers[i + index].nodes.back().setPosition({-1000, -1000});
			layers[i + index].nodes.back().update();
		}
		sf::Color color = Layout::workplaceOutline;
		for (int i : {fps / 2, fps - 1}) {
			layers[i + index].nodes.push_back(node);
			layers[i + index].nodes.back().setPosition(pos2);
			layers[i + index].nodes.back().update();
			layers[i + index].nodes.back().setColor(Animation::getColor(Layout::workplaceBackground, color, 2.f * (i - fps / 2.f) / fps));
		}
		return;
	}
	for (int i : {0, fps / 2 - 1, fps / 2, fps - 1}) {
		layers[i + index].nodes[eid].setPosition(Animation::getVector2f(pos1, pos2, (float)(i + 1) / fps));
		layers[i + index].nodes[eid].update();
	}
}

void Visualizer::removeNode(TreeNode* node)
{
	int eid = -1;
	for (int i = 0; i < (int)layers[index].nodes.size(); ++i) {
		if (layers[index].nodes[i].getValues() == node->getValues()) {
			eid = i;
			break;
		}
	}
	if (eid < 0) return;
	sf::Color color = layers[index].nodes[eid].getColor();
	for (int i : {0, fps / 2 - 1, fps / 2, fps - 1}) {
		layers[i + index].nodes[eid].setColor(Animation::getColor(color, Layout::workplaceBackground, std::min(1.f, 2.f * (i + 1) / fps)));
		if (i >= fps / 2) {
			layers[i + index].nodes[eid].setPosition({ -100, -100 });
			layers[i + index].nodes[eid].update();
		}
	}
	layers[fps - 1 + index].nodes[eid].setPosition({ -100, -100 });
	layers[fps - 1 + index].nodes[eid].update();
}

void Visualizer::removeNode(sf::Vector2f pos)
{
	int eid = -1;
	for (int i = 0; i < (int)layers[index].nodes.size(); ++i) {
		if (layers[index].nodes[i] == Node(pos)) {
			eid = i;
			break;
		}
	}
	if (eid < 0) return;
	sf::Color color = layers[index].nodes[eid].getColor();
	for (int i : {0, fps / 2 - 1, fps / 2, fps - 1}) {
		layers[i + index].nodes[eid].setColor(Animation::getColor(color, Layout::workplaceBackground, std::min(1.f, 2.f * (i + 1) / fps)));
		if (i >= fps / 2) {
			layers[i + index].nodes[eid].setPosition({-100, -100});
			layers[i + index].nodes[eid].update();
		}
	}
	layers[fps - 1 + index].nodes[eid].setPosition({-100, -100});
	layers[fps - 1 + index].nodes[eid].update();
}

void Visualizer::highlightNode(Node* node, sf::Color color)
{
	int eid = -1;
	for (int i = 0; i < (int)layers[index].nodes.size(); ++i) {
		if (layers[index].nodes[i] == *node) {
			eid = i;
			break;
		}
	}
	if (eid < 0) {
		eid = layers[index].nodes.size();
		for (int i : {0, fps / 2 - 1, fps / 2, fps - 1}) {
			layers[i + index].nodes.push_back(*node);
		}
	}
	sf::Color oldColor = layers[index].nodes[eid].getColor();
	for (int i : {0, fps / 2 - 1, fps / 2, fps - 1}) {
		layers[i + index].nodes[eid].setColor(Animation::getColor(oldColor, color, std::min(1.f, 2.f * (i + 1) / fps)));
	}
}

void Visualizer::highlightEdge(Node* u, Node* v, sf::Color color)
{
	int eid = -1;
	for (int i = 0; i < (int)layers[index].edges.size(); ++i) {
		if (layers[index].edges[i] == Edge(u->getCenter(), v->getCenter())) {
			eid = i;
			break;
		}
	}
	if (eid < 0) {
		eid = layers[index].edges.size();
		for (int i : {0, fps / 2 - 1, fps / 2, fps - 1}) {
			layers[i + index].edges.push_back(Edge(u->getCenter(), v->getCenter()));
		}
	}
	sf::Color oldColor = layers[index].edges[eid].getColor();
	for (int i : {0, fps / 2 - 1, fps / 2, fps - 1}) {
		layers[i + index].edges[eid].setColor(Animation::getColor(oldColor, color, std::min(1.f, 2.f * (i + 1) / fps)));
	}
}

bool operator==(std::pair<float, float> a, sf::Vector2f b) {
	return abs(a.first - b.x) <= 1
		&& abs(a.second - b.y) <= 1;
}

void Visualizer::reArrange(TreeNode* root, int autoDelete, int reLayout)
{
	if (!root) return;
	if (reLayout == 1) layoutTree(root);
	std::queue<TreeNode*> q;
	q.push(root);
	
	std::set<std::vector<int>> nodeList;

	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();
		moveNode(node->getOldPosition(), node->getPosition(), *node);
		if (autoDelete) {
			nodeList.insert(node->getValues());
		}
		for (int i = 0; i < node->getChildCount(); ++i) {
			if (node->Child(i)) {
				moveEdge(node->getOldCenter(), node->Child(i)->getOldCenter(), node->getCenter(), node->Child(i)->getCenter());
				q.push(node->Child(i));
			}
		}
	}
	if (autoDelete) {
		for (Node node : layers[index].nodes) {
			if (nodeList.find(node.getValues()) == nodeList.end()) {
				removeNode(node.getPosition());
				removeEdgeFromParent(node.getCenter());
			}
		}
	}
}

void Visualizer::reArrange0(TreeNode *root)
{
	std::queue<TreeNode*> q;
	q.push(root);

	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();
		moveNode(node->getOldPosition(), node->getPosition(), *node);
		for (int i = 0; i < node->getChildCount(); ++i) {
			if (node->Child(i)) {
				moveEdge(node->getOldCenter(), node->Child(i)->getOldCenter(), node->getCenter(), node->Child(i)->getCenter());
				q.push(node->Child(i));
			}
		}
	}
}
