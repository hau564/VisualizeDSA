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

void Tree234::mergeVisualize(TreeNode*& node, int id)
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

void Tree234::insertVisualize(TreeNode*& node, int x)
{
	if (node == nullptr) {
		node = new TreeNode({ x });
		visualizer->duplicateState();
		visualizer->reArrange(root, 1);
		return;
	}
	if (node->getValueCount() == 3) {
		visualizer->duplicateState();
		visualizer->removeNode(node);
		drop(node);
		visualizer->reArrange(root);
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
				
				visualizer->duplicateState();
				visualizer->removeNode(node->Child(i));
				visualizer->removeEdgeFromParent(node->Child(i));
				drop(node->Child(i));
				visualizer->reArrange(root);

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
