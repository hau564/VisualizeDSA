#include "Tree234.hpp"
#include "Tools.hpp"

void Tree234::setup(Visualizer* _visualizer)
{
	visualizer = _visualizer;
	visualizer->addTextbox("Build");
	visualizer->addTextbox("Insert");
	visualizer->addTextbox("Delete");
	visualizer->addTextbox("Search");
}

void Tree234::visualize()
{
	if (!visualizer->newInput) return;

	std::string label, input;
	visualizer->getInput(label, input);

	if (label == "Build") {
		if (!Tools::String::isVectorInt(input)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
		build(Tools::String::toVectorInt(input));
	}
	else if (label == "Insert") {
		if (!Tools::String::isInt(input)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
		insert(Tools::String::toInt(input));

	}
	else if (label == "Delete") {
		if (!Tools::String::isInt(input)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
		Delete(Tools::String::toInt(input));
	}
	else if (label == "Search") {
		if (!Tools::String::isInt(input)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
	}
}

void Tree234::merge(TreeNode*& node, int id)
{
	for (int i = 4; i > id + 1; i--) {
		node->Child(i) = node->Child(i - 1);
	}
	TreeNode* temp = node->Child(id);
	node->Child(id) = temp->Child(0);
	node->Child(id + 1) = temp->Child(1);
	node->addValue(temp->Value(0));
	node->sortValue();
	delete temp;
}

void Tree234::drop(TreeNode*& node)
{
	TreeNode* left = new TreeNode({ node->Value(0) });
	TreeNode* right = new TreeNode({ node->Value(2) });
	left->Child(0) = node->Child(0);
	left->Child(1) = node->Child(1);
	right->Child(0) = node->Child(2);
	right->Child(1) = node->Child(3);

	int x = node->Value(1);
	delete node;
	node = new TreeNode({ x });
	node->Child(0) = left;
	node->Child(1) = right;
}

void Tree234::insertBuild(TreeNode*& node, int x) {
	if (node == nullptr) {
		node = new TreeNode({ x });
		return;
	}
	for (int y : node->getValues())
		if (x == y) return;
	if (node->getValueCount() == 3) {
		drop(node);
	}
	if (node->getRealChildCount() == 0) {
		node->addValue(x);
		node->sortValue();
		return;
	}
	int cnt = node->getValueCount();
	for (int i = 0; i <= cnt; i++) {
		if (x == node->getValue(i)) return;
		if (i == cnt || x < node->Value(i)) {
			if (node->Child(i) && node->Child(i)->getValueCount() == 3) {
				drop(node->Child(i));
				merge(node, i);
				++cnt;
				--i;
				continue;
			}
			insertBuild(node->Child(i), x);
			return;
		}
	}
}

void Tree234::build(std::vector<int> values)
{
	std::cout << "Build ";
	for (int x : values) std::cout << x << " ";
	std::cout << std::endl;

	if (root) {
		delete root;
		root = nullptr;
	}
	for (int x : values) insertBuild(root, x);

	visualizer->layoutTree(root);

	visualizer->clear();
	visualizer->newStep(root);

	visualizer->start();
}

void Tree234::dropVisualize(TreeNode*& node)
{
	visualizer->duplicateState();
	visualizer->removeEdgeFromParent(node);
	visualizer->removeNode(node);
	for (int i = 0; i < 4; i++) {
		if (node->Child(i)) {
			visualizer->removeEdge(node->getCenter(), node->Child(i)->getCenter());
		}
	}

	TreeNode* left = new TreeNode({ node->Value(0) });
	TreeNode* right = new TreeNode({ node->Value(2) });
	left->Child(0) = node->Child(0);
	left->Child(1) = node->Child(1);
	right->Child(0) = node->Child(2);
	right->Child(1) = node->Child(3);

	int x = node->Value(1);
	delete node;
	node = new TreeNode({ x });
	node->Child(0) = left;
	node->Child(1) = right;

	visualizer->reArrange(root);
}

void Tree234::mergeVisualize(TreeNode*& node, int id)
{
	//visualizer->reArrange(node->Child(id), node->getCenter() - (node->Child(id)->getSize() / 2.f));
	
	visualizer->newStep(root);
	visualizer->layoutTreeSkipEdge(root, node, id);
	visualizer->reArrange0(root);
	
	for (int i = 4; i > id + 1; i--) {
		node->Child(i) = node->Child(i - 1);
	}
	TreeNode* temp = node->Child(id);
	node->Child(id) = temp->Child(0);
	node->Child(id + 1) = temp->Child(1);
	node->addValue(temp->Value(0));
	node->sortValue();
	delete temp;
	visualizer->layoutTree(root);
	visualizer->newStep(root);
}

void Tree234::insertVisualize(TreeNode*& node, int x)
{
	if (node == nullptr) {
		node = new TreeNode({ x });
		visualizer->duplicateState();
		visualizer->reArrange(root, 1);
		return;
	}
	for (int y : node->getValues())
		if (x == y) return;
	if (node->getValueCount() == 3) {
		dropVisualize(node);
	}
	if (node->getRealChildCount() == 0) {
		std::vector<int> values = node->getValues();
		values.push_back(x);
		std::sort(values.begin(), values.end());
		delete node;
		node = new TreeNode(values);
		visualizer->duplicateState();
		visualizer->reArrange(root, 1);
		return;
	}
	int cnt = node->getValueCount();
	for (int i = 0; i <= cnt; i++) {
		if (i < cnt && x == node->getValue(i)) return;
		if (i == cnt || x < node->Value(i)) {
			if (node->Child(i) && node->Child(i)->getValueCount() == 3) {
				
				dropVisualize(node->Child(i));

				mergeVisualize(node, i);
				
				++cnt;
				--i;
				continue;
			}
			insertVisualize(node->Child(i), x);
			return;
		}
	}
}

void Tree234::insert(int x)
{
	std::cout << "Insert " << x << std::endl;

	visualizer->clear();
	visualizer->newStep(root);
	insertVisualize(root, x);
	visualizer->newStep(root);
	visualizer->start();

}



void Tree234::removeValue(TreeNode*& node)
{
	if (node->getValueCount() > 1) {
		node->removeValue(0);
		visualizer->newStep(root);
		visualizer->reArrange(root);
		return;
	}

}

void Tree234::deleteNodeValue(TreeNode*& node, int id)
{
	if (node->getRealChildCount() == 0) {
		if (node->getValueCount() > 1) {
			node->removeValue(id);
			visualizer->newStep(root);
			visualizer->reArrange(root);
			return;
		}
		removeValue(node);
		return;
	}
	TreeNode* tmp = node->Child(id + 1);
	while (tmp->Child(0)) tmp = tmp->Child(0);
	std::swap(node->Value(id), tmp->Value(0));

	visualizer->newStep(root);
	removeValue(tmp);
}

void Tree234::deleteVisualize(TreeNode*& node, int x)
{
	if (!node) return;

	for (int i = 0; i < node->getValueCount(); ++i) {
		if (node->getValue(i) == x)
			return deleteNodeValue(node, i);
	}
	int i = 0;
	while (i < node->getValueCount() && x > node->getValue(i)) ++i;
	deleteVisualize(node->Child(i), x);
}

void Tree234::Delete(int x)
{
	std::cout << "Delete " << x << std::endl;
	visualizer->clear();
	visualizer->newStep(root);

	deleteVisualize(root, x);

	visualizer->start();
}
