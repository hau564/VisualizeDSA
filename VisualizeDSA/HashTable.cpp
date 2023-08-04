#include "HashTable.hpp"
#include "Tools.hpp"

void HashTable::setup(Visualizer* _visualizer)
{
	visualizer = _visualizer;
	visualizer->addTextbox("Size");
	visualizer->addTextbox("Insert");
	visualizer->addTextbox("Delete");
	visualizer->addTextbox("Search");
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
	visualizer->newStep(arr[0]);
	visualizer->start();
}

void HashTable::insert(int _x)
{
	if (!arr.size()) return;

	visualizer->clear();
	visualizer->newStep(arr[0]);

	int i = _x % arr.size();
	int p = i;
	
	visualizer->duplicateState();
	visualizer->highlightNode(arr[i]);
	visualizer->duplicateState();

	while (arr[i]->getValues().size()) {
		visualizer->duplicateState();
		visualizer->highlightNode(arr[i], Color::normal);
		i = (i + 1) % (int)arr.size();
		visualizer->duplicateState();
		visualizer->highlightNode(arr[i]);
		visualizer->duplicateState();
		if (i == p || (arr[i]->getValues().size() && arr[i]->Value() == _x)) {
			visualizer->newStep(arr[0]);
			visualizer->start();
			return;
		}
	}

	arr[i]->create({ _x });
	arr[i]->Shape().setCornersRadius(1);
	sf::Vector2f pos = Layout::DisplayScreen::basePos;
	for (int i = 0; i < (int)arr.size(); i++) {
		arr[i]->setPosition(pos);
		pos.x += arr[i]->getSize().x + 2 * arr[i]->Shape().getOutlineThickness();
	}

	visualizer->newStep(arr[0]);
	visualizer->start();
}

void HashTable::Delete(int _x)
{
	if (!arr.size()) return;

	visualizer->clear();
	visualizer->newStep(arr[0]);

	int i = mainSearch(_x);
	if (i >= 0) {
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
	visualizer->newStep(arr[0]);
	visualizer->start();
}

int HashTable::mainSearch(int _x)
{
	int i = _x % arr.size();
	int p = i;

	visualizer->duplicateState();
	visualizer->highlightNode(arr[i]);
	visualizer->duplicateState();

	while (arr[i]->getValues().size()) {
		if (arr[i]->Value() == _x) {
			visualizer->duplicateState();
			visualizer->highlightNode(arr[i], Color::found);
			visualizer->duplicateState();
			visualizer->highlightNode(arr[i], Color::normal);
			visualizer->start();
			return i;
		}

		visualizer->duplicateState();
		visualizer->highlightNode(arr[i], Color::normal);
		i = (i + 1) % (int)arr.size();
		visualizer->duplicateState();
		visualizer->highlightNode(arr[i]);
		visualizer->duplicateState();

		if (i == p) {
			visualizer->newStep(arr[0]);
			visualizer->start();
			return - 1;
		}
	}

	return -1;
}

void HashTable::search(int _x)
{
	if (!arr.size()) return;

	visualizer->clear();
	visualizer->newStep(arr[0]);

	mainSearch(_x);

	visualizer->newStep(arr[0]);
	visualizer->start();
}
