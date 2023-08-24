#include "Trie.hpp"

void Trie::setup(Visualizer* _visualizer)
{
	visualizer = _visualizer;
	visualizer->setTextboxes({ "Build", "Insert", "Delete", "Search" });
	/*visualizer->addTextbox("Build");
	visualizer->addTextbox("Insert");
	visualizer->addTextbox("Delete");
	visualizer->addTextbox("Search");*/
}

void Trie::visualize()
{
	if (!visualizer->newInput) return;

	std::string label, input;
	visualizer->getInput(label, input);

	if (label == "Build") {
		if (!Tools::String::isVectorAlphabet(input)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
		build(Tools::String::toVectorString(input));
	}
	else if (label == "Insert") {
		if (!Tools::String::isAlphaString(input)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
		insert(Tools::String::toAlphaString(input));
	}
	else if (label == "Delete") {
		if (!Tools::String::isAlphaString(input)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
		Delete(Tools::String::toAlphaString(input));
	}
	else if (label == "Search") {
		if (!Tools::String::isAlphaString(input)) {
			std::cout << "Invalid Input: " << input << std::endl;
			return;
		}
		search(Tools::String::toAlphaString(input));
	}
}

void Trie::insertBuild(TreeNode* root, std::string s)
{
	std::vector<int> t;
	root->height++;
	for (int i = 0; i < (int)s.size(); ++i) {
		t.push_back(s[i]);
		if (root->Child(s[i] - 'a') == nullptr) {
			root->Child(s[i] - 'a') = new TreeNode({t.back()});
			root->Child(s[i] - 'a')->setStringNode();
			root->Child(s[i] - 'a')->update();
		}
		root = root->Child(s[i] - 'a');
		root->height++;
	}
	root->setColor(Color::mark);
}

void Trie::build(std::vector<std::string> values)
{
	if (root) {
		Tools::Tree::killTree(root);
		root = nullptr;
	}
	root = new TreeNode({' '});
	root->setStringNode();
	for (std::string s : values) {
		insertBuild(root, s);
	}

	visualizer->layoutTree(root);

	visualizer->clear();
	visualizer->setSource({});
	visualizer->newStep(root);
	visualizer->start();
}

void Trie::insertVisualize(TreeNode* node, std::string s)
{
	visualizer->duplicateState();
	visualizer->highlightNode(node);

	std::vector<int> t;
	node->height++;
	for (int i = 0; i < (int)s.size(); ++i) {
		t.push_back(s[i]);
		if (node->Child(s[i] - 'a') == nullptr) {
			node->Child(s[i] - 'a') = new TreeNode({t.back()});
			node->Child(s[i] - 'a')->setStringNode();
			node->Child(s[i] - 'a')->update();
			visualizer->duplicateState();
			visualizer->reArrange(root);
		}
		visualizer->duplicateState();
		visualizer->highlightNode(node->Child(s[i] - 'a'));
		visualizer->highlightEdge(node, node->Child(s[i] - 'a'));
		visualizer->duplicateState();
		node = node->Child(s[i] - 'a');
		node->height++;
	}
	node->setColor(Color::mark);
}

void Trie::insert(std::string s)
{
	if (!root) {
		root = new TreeNode({ ' ' });
		root->setStringNode();
	}

	visualizer->clear();

	visualizer->layoutTree(root);
	visualizer->newStep(root);
	
	insertVisualize(root, s);

	visualizer->duplicateState();
	visualizer->layoutTree(root);
	visualizer->newStep(root);
	visualizer->start();
}

void Trie::deleteVisualize(TreeNode*& node, std::string s, int i)
{
	visualizer->duplicateState();
	visualizer->highlightNode(node);
	if (i < (int)s.size()) {
		if (node->Child(s[i] - 'a') != nullptr) {
			node->height -= node->Child(s[i] - 'a')->height;

			visualizer->duplicateState();
			visualizer->highlightEdge(node, node->Child(s[i] - 'a'));
			
			deleteVisualize(node->Child(s[i] - 'a'), s, i + 1);

			if (node->Child(s[i] - 'a')) {
				visualizer->highlightEdge(node, node->Child(s[i] - 'a'), Color::normal);
				node->height += node->Child(s[i] - 'a')->height;
			}
		}
	}
	else {
		int cnt = 0;
		for (int i = 0; i < 26; ++i) 
			if (node->Child(i)) cnt += node->Child(i)->height;
		if (cnt < node->height) {
			node->height--;
		}
	}

	if (!node->height) {
		visualizer->duplicateState();
		visualizer->removeNode(node->getPosition());
		visualizer->removeEdgeFromParent(node);
		delete node;
		node = nullptr;
		return;
	}
	visualizer->duplicateState();
	visualizer->highlightNode(node, Color::normal);
}

void Trie::Delete(std::string s)
{
	if (!root) {
		root = new TreeNode({ ' ' });
		root->setStringNode();
	}

	visualizer->clear();

	visualizer->layoutTree(root);
	visualizer->newStep(root);

	deleteVisualize(root, s);

	visualizer->duplicateState();
	visualizer->reArrange(root);
	visualizer->start();
}

void Trie::search(std::string s)
{
	if (!root) {
		root = new TreeNode({ ' ' });
		root->setStringNode();
	}

	visualizer->clear();
	visualizer->setSource({
		"Node* cur = root",
		"for each char c in string:",
		"	cur = cur->child(c - 'a')",
		"	if (!cur) return not found",
		"return cur"
		});

	visualizer->layoutTree(root);
	visualizer->newStep(root, "#");

	visualizer->duplicateState("Node* cur = root");
	visualizer->highlightNode(root);
	visualizer->duplicateState("for each char c in string:");

	TreeNode* cur = root;
	for (char c : s) {
		visualizer->duplicateState("	cur = cur->child(c - 'a')");
		if (cur->Child(c - 'a')) {
			visualizer->highlightEdge(cur, cur->Child(c - 'a'));
		}
		visualizer->duplicateState("	if (!cur) return not found");
		cur = cur->Child(c - 'a');
		if (!cur) {
			visualizer->newStep(root, "#");
			visualizer->start();
			return;
		}
		visualizer->highlightNode(cur);
		visualizer->duplicateState("for each char c in string:");
		
	}

	visualizer->duplicateState("return cur");
	visualizer->highlightNode(cur, Color::found);
	visualizer->newStep(root, "#");

	visualizer->start();
}
