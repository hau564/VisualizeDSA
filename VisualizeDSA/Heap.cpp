#include "Heap.hpp"
#include "Tools.hpp"

void Heap::setup(Visualizer* _visualizer)
{
	visualizer = _visualizer;
	visualizer->addTextbox("Build");
	visualizer->addTextbox("Insert");
	visualizer->addTextbox("DeleteId");
	visualizer->addTextbox("Get");
}

void Heap::visualize()
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
	else if (label == "DeleteId") {
		if (!Tools::String::isInt(input)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
		Delete(Tools::String::toInt(input));
	}
	else if (label == "Get") {
		if (!Tools::String::isInt(input)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
		Get();
	}
}

void Heap::build(std::vector<int> values)
{
	std::cout << "Build ";
	for (int x : values) std::cout << x << " ";
	std::cout << std::endl;

	while (!tree.empty()) {
		delete tree.back();	
		tree.pop_back();
	}

	for (int x : values) {
		tree.push_back(new TreeNode({ x }));
		int i = tree.size() - 1;
		if (i) {
			tree[(i - 1) / 2]->Child((i & 1) ^ 1) = tree[i];
		}
		while (i && !cmp(tree[(i - 1) / 2]->Value(), tree[i]->Value())) {
			std::swap(tree[i]->Value(), tree[(i - 1) / 2]->Value());
			i = (i - 1) / 2;
		}
	}

	for (TreeNode* node : tree) node->update();

	visualizer->clear();
	if (tree.size()) {
		visualizer->layoutTree(tree[0], Layout::DisplayScreen::basePos);
		visualizer->newStep(tree[0]);
	}
	else visualizer->newStep();
	visualizer->start();
}

void Heap::swapVisualize(int i, int j)
{
	visualizer->moveNode(tree[i]->getPosition(), tree[j]->getPosition());
	visualizer->moveNode(tree[j]->getPosition(), tree[i]->getPosition());
}

void Heap::heapUpVisualize(int &i)
{
	visualizer->duplicateState();
	visualizer->highlightNode(tree[i]);
	while (i && !cmp(tree[(i - 1) / 2]->Value(), tree[i]->Value())) {
		std::swap(tree[i]->Value(), tree[(i - 1) / 2]->Value());
		visualizer->duplicateState();
		visualizer->highlightNode(tree[(i - 1) / 2]);

		visualizer->duplicateState();
		visualizer->highlightNode(tree[(i - 1) / 2], Color::normal);
		swapVisualize(i, (i - 1) / 2);

		i = (i - 1) / 2;
	}
	visualizer->duplicateState();
	visualizer->highlightNode(tree[i], Color::normal);

	for (TreeNode* node : tree) node->update();
}

void Heap::insert(int x)
{
	std::cout << "Insert " << x << std::endl;

	visualizer->clear();
	if (tree.size()) {
		visualizer->layoutTree(tree[0], Layout::DisplayScreen::basePos);
		visualizer->newStep(tree[0]);
	}
	else visualizer->newStep();

	tree.push_back(new TreeNode({ x }));
	int i = tree.size() - 1;
	if (i) {
		tree[(i - 1) / 2]->Child((i & 1) ^ 1) = tree[i];
		visualizer->duplicateState();
		visualizer->reArrange(tree[0]);
	}
	heapUpVisualize(i);

	visualizer->layoutTree(tree[0]);
	visualizer->newStep(tree[0]);
	visualizer->start();
}

void Heap::heapDownVisualize(int &i)
{
	visualizer->duplicateState();
	visualizer->highlightNode(tree[i]);

	int flag = 1;
	while (flag && i * 2 < (int)tree.size() - 1) {
		int j = i * 2 + 1;
		if (j < (int)tree.size() - 1 && !cmp(tree[j]->Value(), tree[j + 1]->Value())) ++j;
		std::cout << i << " " << j << std::endl;
		if (!cmp(tree[i]->Value(), tree[j]->Value())) {
			std::swap(tree[i]->Value(), tree[j]->Value());
			visualizer->duplicateState();
			visualizer->highlightNode(tree[j]);

			visualizer->duplicateState();
			visualizer->highlightNode(tree[j], Color::normal);
			swapVisualize(i, j);

			i = j;
		}
		else flag = 0;
	}

	visualizer->duplicateState();
	visualizer->highlightNode(tree[i], Color::normal);

	for (TreeNode* node : tree) node->update();
}

void Heap::Delete(int id)
{
	std::cout << "Delete " << id << std::endl;
	if (id >= (int)tree.size()) {
		return;
	}

	visualizer->clear();
	visualizer->newStep(tree[0]);

	int i = tree.size() - 1;

	if (i) {
		std::swap(tree[id]->Value(), tree[i]->Value());
		visualizer->duplicateState();
		visualizer->highlightNode(tree[id]);
		visualizer->highlightNode(tree[i]);
		visualizer->duplicateState();
		visualizer->moveNode(tree[id]->getPosition(), tree[i]->getPosition());
		visualizer->moveNode(tree[i]->getPosition(), tree[id]->getPosition());
	}

	visualizer->duplicateState();
	visualizer->removeNode(tree[i]);
	visualizer->removeEdgeFromParent(tree[i]);
	delete tree[i];
	tree.pop_back();
	if (i) tree[(i - 1) / 2]->Child((i & 1) ^ 1) = nullptr;
	else {
		visualizer->start();
		return;
	}

	visualizer->newStep(tree[0]);
	heapUpVisualize(id);

	visualizer->newStep(tree[0]);
	heapDownVisualize(id);

	visualizer->layoutTree(tree[0]);
	visualizer->newStep(tree[0]);
	visualizer->start();
}

void Heap::Get()
{
	std::cout << "Get" << std::endl;
	if (tree.empty()) return;
	
	visualizer->clear();
	visualizer->newStep(tree[0]);

	visualizer->highlightNode(tree[0]);
	visualizer->duplicateState();
	visualizer->highlightNode(tree[0], Color::normal);
	visualizer->start();
}
