#include "Visualizer.hpp"
#include "Layout.hpp"
#include <queue>

void Visualizer::setup()
{
	Display::setup();
	InputTable::setup();
}

void Visualizer::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	Display::handleEvent(window, event);	
	InputTable::handleEvent(window, event);
}

void Visualizer::update()
{
	Display::update();
	InputTable::update();
}

void Visualizer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Display::draw(target, states);
	InputTable::draw(target, states);
}

void dfsLayout(TreeNode* root, sf::Vector2f &pos, float horizontalSpacing, float verticalSpacing) {
	if (root == nullptr) return;
	int cntChild = root->getChildCount();
	for (int i = 0; i < (cntChild + 1) / 2; ++i) {
		pos.y += verticalSpacing;
		dfsLayout(root->Child(i), pos, horizontalSpacing, verticalSpacing);
		pos.y -= verticalSpacing;
	}
	root->memorizePosition();
	root->setPosition(pos);
	pos.x += horizontalSpacing + root->getSize().x;
	for (int i = (cntChild + 1) / 2; i < cntChild; ++i) {
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

void Visualizer::newStep()
{
	index = layers.size();
	for (int i = 0; i < fps; ++i) {
		addLayer(Layer(), 1.0f / fps);
	}
}

void Visualizer::newStep(TreeNode* root)
{
	newStep();
	addTree(root);
}

void Visualizer::duplicateState()
{
	index = layers.size();
	if (index)
		for (int i = 0; i < fps; ++i) {
			addLayer(layers[index - 1], 1.f / fps);
		}
	else
		newStep();
}

void Visualizer::addTree(TreeNode* root)
{
	for (int i = 0; i < fps; ++i) 
		layers[index + i].addTree(root);
}

void Visualizer::moveEdge(Node* u, Node* v, Node* uu, Node* vv)
{
	moveEdge(u->getPosition(), v->getPosition(), uu->getPosition(), vv->getPosition());
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
		for (int i = 0; i < fps; ++i) {
			layers[i + index].edges.push_back(Edge(u, u));
		}
		v = u;
	}
	for (int i = 0; i < fps; ++i) {
		layers[i + index].edges[eid].create(getAnimationPosition(u, uu, (float)(i + 1) / fps), getAnimationPosition(v, vv, (float)(i + 1) / fps), layers[i + index].edges[eid].getColor());
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
	for (int i = 0; i < fps; ++i) {
		layers[i + index].edges[eid].create(u, v, getAnimationColor(color, Layout::workplaceBackground, 1.f * (i + 1) / fps));
	}
}

void Visualizer::removeEdgeFromParent(Node* v)
{
	removeEdgeFromParent(v->getCenter());
}

bool operator == (sf::Vector2f pos1, sf::Vector2f pos2) {
	return abs(pos1.x - pos2.x) <= 0.0001
		&& abs(pos1.y - pos2.y) <= 0.0001;
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
		for (int i = 0; i < fps; ++i) {
			layers[i + index].nodes.push_back(Node({-1000, -1000}, _values));
		}
		layers[fps - 1 + index].nodes.back() = Node(pos2, _values);
		return;
	}
	for (int i = 0; i < fps; ++i) {
		layers[i + index].nodes[eid].setPosition(getAnimationPosition(pos1, pos2, (float)(i + 1) / fps));
		layers[i + index].nodes[eid].update();
	}
}

void Visualizer::removeNode(TreeNode* node)
{
	removeNode(node->getPosition());
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
	for (int i = 0; i < fps; ++i) {
		layers[i + index].nodes[eid].setColor(getAnimationColor(color, Layout::workplaceBackground, 1.f * (i + 1) / fps));
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
		for (int i = 0; i < fps; ++i) {
			layers[i + index].nodes.push_back(*node);
		}
	}
	sf::Color oldColor = layers[index].nodes[eid].getColor();
	for (int i = 0; i < fps; ++i) {
		float r = getByRatio(oldColor.r, color.r, 1.f * (i + 1) / fps);
		float g = getByRatio(oldColor.g, color.g, 1.f * (i + 1) / fps);
		float b = getByRatio(oldColor.b, color.b, 1.f * (i + 1) / fps);
		layers[i + index].nodes[eid].setColor(sf::Color(r, g, b));
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
		for (int i = 0; i < fps; ++i) {
			layers[i + index].edges.push_back(Edge(u->getCenter(), v->getCenter()));
		}
	}
	sf::Color oldColor = layers[index].edges[eid].getColor();
	for (int i = 0; i < fps; ++i) {
		float r = getByRatio(oldColor.r, color.r, 1.f * (i + 1) / fps);
		float g = getByRatio(oldColor.g, color.g, 1.f * (i + 1) / fps);
		float b = getByRatio(oldColor.b, color.b, 1.f * (i + 1) / fps);
		layers[i + index].edges[eid].setColor(sf::Color(r, g, b));
	}
}

float Visualizer::getByRatio(float x, float y, float r)
{
	return x + (y - x) * r;
}

sf::Vector2f Visualizer::getAnimationPosition(sf::Vector2f pos1, sf::Vector2f pos2, float r)
{
	return sf::Vector2f(pos1.x + (pos2.x - pos1.x) * r, pos1.y + (pos2.y - pos1.y) * r);
}

void Visualizer::reArrange(TreeNode* root)
{
	if (!root) return;
	layoutTree(root);
	std::queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();
		moveNode(node->getOldPosition(), node->getPosition(), node->getValues());
		for (int i = 0; i < node->getChildCount(); ++i) {
			if (node->Child(i)) {
				moveEdge(node->getOldCenter(), node->Child(i)->getOldCenter(), node->getCenter(), node->Child(i)->getCenter());
				q.push(node->Child(i));
			}
		}
	}
}

sf::Color Visualizer::getAnimationColor(sf::Color color1, sf::Color color2, float r)
{
	return sf::Color(getByRatio(color1.r, color2.r, r), getByRatio(color1.g, color2.g ,r), getByRatio(color1.b, color2.b, r));
}

