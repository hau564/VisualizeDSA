#include "HashTable.hpp"
#include "Tools.hpp"

void HashTable::setup(Visualizer* _visualizer)
{
	visualizer = _visualizer;
	visualizer->setTextboxes({
		"Size",
		"Insert",
		"Delete",
		"Search"
		});
	/*visualizer->addTextbox("Size");
	visualizer->addTextbox("Insert");
	visualizer->addTextbox("Delete");
	visualizer->addTextbox("Search");*/
}

void HashTable::visualize()
{
	if (!visualizer->newInput) return;

	std::string label, input;
	visualizer->getInput(label, input);

	if (label == "Size") {
		if (!Tools::String::isInt(input)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
		create(Tools::String::toInt(input));
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
		search(Tools::String::toInt(input));
	}
}

void HashTable::create(int n)
{
	for (TreeNode* node : arr) delete node;
	arr.clear();
	arr.resize(n);
	sf::Vector2f pos = Layout::DisplayScreen::basePos;
	for (int i = 0; i < n; i++) {
		arr[i] = new TreeNode({});
		arr[i]->setPosition(pos);
		arr[i]->Shape().setCornersRadius(1);
		pos.x += arr[i]->getSize().x + 2 * arr[i]->Shape().getOutlineThickness();
		if (i) arr[i - 1]->Child(0) = arr[i];
	}

	visualizer->clear();
	visualizer->setSource({ "table = array(n)" });
	visualizer->newStep(arr[0]);
	visualizer->start();
}

void HashTable::insert(int _x)
{
	if (!arr.size()) return;
	for (Node* node : arr) {
		if (node->getValues().size() && !node->stringNode && node->getValues()[0] == _x) return;
	}

	visualizer->clear();
	visualizer->setSource({
		"i = hash(x) // = x % size",
		"while table[i] has a real value:",
		"	i = (i + 1) mod size",
		"	if (i == hash(x) return",
		"table[i] = x",
	});

	visualizer->newStep(arr[0], "#");

	int i = _x % arr.size();
	int p = i;
	
	visualizer->duplicateState("i = hash(x) // = x % size");

	visualizer->duplicateState("while table[i] has a real value:");
	visualizer->highlightNode(arr[i]);
	while (arr[i]->getValues().size() && !arr[i]->stringNode) {
		visualizer->duplicateState("	i = (i + 1) mod size");
		visualizer->duplicateState("	if (i == hash(x) return");
		visualizer->highlightNode(arr[i], Color::normal);
		i = (i + 1) % (int)arr.size();
		visualizer->highlightNode(arr[i]);
		if (i == p) {
			visualizer->newStep(arr[0], "#");
			visualizer->start();
			return;
		}
		visualizer->duplicateState("while table[i] has a real value:");
	}

	arr[i]->setStringNode(false);
	visualizer->duplicateState("table[i] = x");
	arr[i]->create({ _x });
	arr[i]->Shape().setCornersRadius(1);
	sf::Vector2f pos = Layout::DisplayScreen::basePos;
	for (int i = 0; i < (int)arr.size(); i++) {
		arr[i]->setPosition(pos);
		pos.x += arr[i]->getSize().x + 2 * arr[i]->Shape().getOutlineThickness();
	}

	visualizer->newStep(arr[0], "#");
	visualizer->start();
}

void HashTable::Delete(int _x)
{
	if (!arr.size()) return;

	visualizer->clear();
	visualizer->setSource({
		"i = Search(x)",
		"if (i >= 0) table[i] = dummy value",
	});
	visualizer->newStep(arr[0], "#");

	int i = _x % arr.size();
	while (arr[i]->getValues().size() && arr[i]->Value() != _x) {
		i = (i + 1) % (int)arr.size();
		if (i == _x % arr.size()) {
			i = -1;
			break;
		}
	}
	if (arr[i]->getValues().empty()) i = -1;

	visualizer->duplicateState("i = Search(x)");
	visualizer->duplicateState("if (i >= 0) table[i] = dummy value");
	if (i >= 0) {
		visualizer->highlightNode(arr[i]);
		arr[i]->create({'_'});
		arr[i]->setStringNode();
		arr[i]->Shape().setCornersRadius(1);
		arr[i]->update();
		sf::Vector2f pos = Layout::DisplayScreen::basePos;
		for (int i = 0; i < (int)arr.size(); i++) {
			arr[i]->setPosition(pos);
			pos.x += arr[i]->getSize().x + 2 * arr[i]->Shape().getOutlineThickness();
		}
	}
	visualizer->newStep(arr[0], "#");
	visualizer->start();
}

int HashTable::mainSearch(int _x)
{
	int i = _x % arr.size();
	int p = i;

	visualizer->duplicateState("i = hash(x) // = x % size");
	visualizer->highlightNode(arr[i]);

	visualizer->duplicateState("while table[i] is not empty");
	while (arr[i]->getValues().size()) {
		visualizer->duplicateState("	if (table[i] == x) return i");
		if (arr[i]->Value() == _x) {
			visualizer->duplicateState();
			visualizer->highlightNode(arr[i], Color::found);
			visualizer->duplicateState("#");
			visualizer->highlightNode(arr[i], Color::normal);
			visualizer->start();
			return i;
		}

		visualizer->duplicateState("	i = (i + 1) mod size");
		visualizer->duplicateState("	if (i == hash(x)) return -1");
		visualizer->highlightNode(arr[i], Color::normal);
		i = (i + 1) % (int)arr.size();
		visualizer->highlightNode(arr[i]);

		if (i == p) {
			visualizer->newStep(arr[0], "#");
			visualizer->start();
			return -1;
		}
		visualizer->duplicateState("while table[i] is not empty");
	}

	visualizer->duplicateState("return -1");
	return -1;
}

void HashTable::search(int _x)
{
	if (!arr.size()) return;

	visualizer->clear();
	visualizer->setSource({
		"i = hash(x) // = x % size",
		"while table[i] is not empty",
		"	if (table[i] == x) return i",
		"	i = (i + 1) mod size",
		"	if (i == hash(x)) return -1",
		"return -1",
	});
	visualizer->newStep(arr[0]);

	mainSearch(_x);

	visualizer->newStep(arr[0], "#");
	visualizer->start();
}
