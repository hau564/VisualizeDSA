#include "Heap.hpp"
#include "Tools.hpp"

void Heap::setup(Visualizer* _visualizer)
{
	visualizer = _visualizer;
	visualizer->setTextboxes({ "Build", "Insert", "DeleteId", "Get" });
	/*visualizer->addTextbox("Build");
	visualizer->addTextbox("Insert");
	visualizer->addTextbox("DeleteId");
	visualizer->addTextbox("Get");*/
}

void Heap::setMinHeap()
{
	cmp = [](int a, int b) { return a <= b; };
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
	visualizer->setSource({});
	if (tree.size()) {
		for (int i = 0; i < (int)tree.size(); ++i) {
			tree[i]->height = i;
			tree[i]->showHeight();
			tree[i]->heightText.setCharacterSize(17);
		}
		visualizer->layoutTree(tree[0], Layout::DisplayScreen::basePos);
		visualizer->newStep(tree[0]);
		for (int i = 0; i < (int)tree.size(); ++i)
			tree[i]->showHeight(0);
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
	visualizer->duplicateState("while i > 0 and !compare(heap[(i - 1) / 2], heap[i]):");
	visualizer->highlightNode(tree[i]);
	while (i && !cmp(tree[(i - 1) / 2]->Value(), tree[i]->Value())) {
		std::swap(tree[i]->Value(), tree[(i - 1) / 2]->Value());
		visualizer->duplicateState("	swap(heap[i], heap[i = (i - 1) / 2])");
		visualizer->highlightNode(tree[(i - 1) / 2]);

		visualizer->duplicateState("while i > 0 and !compare(heap[(i - 1) / 2], heap[i]):");
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
	visualizer->setSource({
		"heap[i = size++] = x",
		"// if min heap: compare = (a < b)",
		"// if max heap: compare = (a > b)",
		"while i > 0 and !compare(heap[(i - 1) / 2], heap[i]):",
		"	swap(heap[i], heap[i = (i - 1) / 2])",
		});
	if (tree.size()) {
		visualizer->layoutTree(tree[0], Layout::DisplayScreen::basePos);
		visualizer->newStep(tree[0]);
	}
	else visualizer->newStep();

	tree.push_back(new TreeNode({ x }));
	int i = tree.size() - 1;
	visualizer->duplicateState("heap[i = size++] = x");
	if (i) {
		tree[(i - 1) / 2]->Child((i & 1) ^ 1) = tree[i];
		visualizer->reArrange(tree[0]);
	}
	heapUpVisualize(i);

	visualizer->layoutTree(tree[0]);
	visualizer->newStep(tree[0], "#");
	visualizer->start();
}

void Heap::heapDownVisualize(int &i)
{
	visualizer->duplicateState("while !compare(heap[i], better_child_of(i)):");
	visualizer->highlightNode(tree[i]);

	int flag = 1;
	while (flag && i * 2 < (int)tree.size() - 1) {
		int j = i * 2 + 1;
		if (j < (int)tree.size() - 1 && !cmp(tree[j]->Value(), tree[j + 1]->Value())) ++j;
		std::cout << i << " " << j << std::endl;
		if (!cmp(tree[i]->Value(), tree[j]->Value())) {
			std::swap(tree[i]->Value(), tree[j]->Value());
			visualizer->duplicateState("	swap(heap[i], better_child_of(i))");
			visualizer->highlightNode(tree[j]);

			visualizer->duplicateState("while !compare(heap[i], better_child_of(i)):");
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
	visualizer->setSource({
		"swap(heap[i], heap[--size])",
		"while i > 0 and !compare(heap[(i - 1) / 2], heap[i]):",
		"	swap(heap[i], heap[i = (i - 1) / 2])",
		"while !compare(heap[i], better_child_of(i)):",
		"	swap(heap[i], better_child_of(i))",
		});
	visualizer->newStep(tree[0]);

	int i = tree.size() - 1;

	visualizer->duplicateState("swap(heap[i], heap[--size])");
	if (i) {
		std::swap(tree[id]->Value(), tree[i]->Value());
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

	visualizer->newStep(tree[0], "#");
	visualizer->reArrange(tree[0]);
	visualizer->start();
}

void Heap::Get()
{
	std::cout << "Get" << std::endl;
	if (tree.empty()) return;
	
	visualizer->clear(); 
	visualizer->setSource({ "return heap[0]" });
	
	for (int i = 0; i < (int)tree.size(); ++i) {
		tree[i]->height = i;
		tree[i]->showHeight();
		tree[i]->heightText.setCharacterSize(17);
	}

	visualizer->newStep(tree[0]);
	visualizer->newStep(tree[0], "return heap[0]");

	visualizer->highlightNode(tree[0], Color::found);
	visualizer->duplicateState("#");
	visualizer->highlightNode(tree[0], Color::normal);

	for (int i = 0; i < (int)tree.size(); ++i)
		tree[i]->showHeight(0);

	visualizer->start();
}
