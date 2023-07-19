#include "AVL.hpp"
#include "Tools.hpp"
#include "Layout.hpp"
#include <queue>
#include <stack>

void AVL::setup(Visualizer& _visualizer)
{
	visualizer = &_visualizer;
	visualizer->addTextbox("Build");
	visualizer->addTextbox("Insert");
	visualizer->addTextbox("Delete");
	visualizer->addTextbox("Search");
}

void AVL::visualize()
{
	if (!visualizer->newInput) return;

	std::string label, input;
	visualizer->getInput(label, input);

	if (label == "Build") {
		if (!Tools::String::isVectorInt(input)) {
			std::cout << "Invalid Input:" << input << std::endl;
			return;
		}
		build(Tools::String::toVectorInt(input));
	}
	else if (label == "Insert") {
		if (!Tools::String::isInt(input)) {
			std::cout << "Invalid Input:" << input << std::endl;
			return;
		}
		insert(Tools::String::toInt(input));
	}
	else if (label == "Delete") {
		if (!Tools::String::isInt(input)) {
			std::cout << "Invalid Input:" << input << std::endl;
			return;
		}
		Delete(Tools::String::toInt(input));
	}
	else if (label == "Search") {
		if (!Tools::String::isInt(input)) {
			std::cout << "Invalid Input:" << input << std::endl;
			return;
		}
		search(Tools::String::toInt(input));
	}
}

void rotateRight(TreeNode*& root) {
	TreeNode* left = root->Child(0);
	root->Child(0) = left->Child(1);
	left->Child(1) = root;
	root->update();
	root = left;
	root->update();
}

void rotateLeft(TreeNode*& root) {
	TreeNode* right = root->Child(1);
	root->Child(1) = right->Child(0);
	right->Child(0) = root;
	root->update();
	root = right;
	root->update();
}

void insertBuild(TreeNode*& root, int x) {
	if (root == nullptr) {
		root = new TreeNode({ x });
		return;
	}
	if (root->Value() == x) return;
	if (root->Value() > x) {
		insertBuild(root->Child(0), x);
	}
	else {
		insertBuild(root->Child(1), x);
	}
	root->update();
	if (abs(root->getChildHeight(0) - root->getChildHeight(1)) > 1) {
		if (root->getChildHeight(0) > root->getChildHeight(1)) {
			if (root->Child(0)->getChildHeight(1) > root->Child(0)->getChildHeight(0)) {
				rotateLeft(root->Child(0));
			}
			rotateRight(root);
		}
		else {
			if (root->Child(1)->getChildHeight(0) > root->Child(1)->getChildHeight(1)) {
				rotateRight(root->Child(1));
			}
			rotateLeft(root);
		}
	}
}

void AVL::build(std::vector<int> values)
{
	std::cout << "Build ";
	for (int x : values) std::cout << x << " ";
	std::cout << std::endl;	

	if (root) {
		delete root;
		root = nullptr;
	}
	for (int x : values) {
		insertBuild(root, x);
	}

	visualizer->layoutTree(root, Layout::DisplayScreen::basePos);

	visualizer->clear();
	visualizer->newStep(root);
	
	visualizer->start();
}

void AVL::rotateRightVisualize(TreeNode*& node)
{
	visualizer->duplicateState();
	visualizer->removeEdgeFromParent(node);
	visualizer->removeEdgeFromParent(node->Child(0));
	if (node->Child(0)->Child(1)) visualizer->removeEdgeFromParent(node->Child(0)->Child(1));
	rotateRight(node);
	visualizer->reArrange(root);
}

void AVL::rotateLeftVisualize(TreeNode*& node)
{
	visualizer->duplicateState();
	visualizer->removeEdgeFromParent(node);
	visualizer->removeEdgeFromParent(node->Child(1));
	if (node->Child(1)->Child(0)) visualizer->removeEdgeFromParent(node->Child(1)->Child(0));
	rotateLeft(node);
	visualizer->reArrange(root);
}

void AVL::balanceVisualize(TreeNode*& node)
{
	if (abs(node->getChildHeight(0) - node->getChildHeight(1)) > 1) {
		if (node->getChildHeight(0) > node->getChildHeight(1)) {
			if (node->Child(0)->getChildHeight(1) > node->Child(0)->getChildHeight(0)) {
				rotateLeftVisualize(node->Child(0));
				visualizer->duplicateState();
			}
			rotateRightVisualize(node);
		}
		else {
			if (node->Child(1)->getChildHeight(0) > node->Child(1)->getChildHeight(1)) {
				rotateRightVisualize(node->Child(1));
				visualizer->duplicateState();
			}
			rotateLeftVisualize(node);
		}
	}
}

void AVL::insertVisualize(TreeNode*& node, int x) {
	if (node == nullptr) {
		visualizer->duplicateState();
		node = new TreeNode({ x });
		visualizer->reArrange(root);
		return;
	}
	
	visualizer->duplicateState();
	visualizer->highlightNode(node);

	if (node->getValue() == x) {
		visualizer->duplicateState();
		visualizer->highlightNode(node, Color::normal);
		return;
	}
	if (node->Value() > x) {
		if (node->Child(0)) {
			visualizer->duplicateState();
			visualizer->highlightEdge(node, node->Child(0));
		}
		insertVisualize(node->Child(0), x);
		visualizer->duplicateState();
		visualizer->highlightEdge(node, node->Child(0), Color::normal);
	}
	else {
		if (node->Child(1)) {
			visualizer->duplicateState();
			visualizer->highlightEdge(node, node->Child(1));
		}
		insertVisualize(node->Child(1), x);
		visualizer->duplicateState();
		visualizer->highlightEdge(node, node->Child(1), Color::normal);
	}
	node->update(); 
	visualizer->duplicateState();
	visualizer->highlightNode(node, Color::normal);
	balanceVisualize(node);
}

void AVL::insert(int x)
{
	std::cout << "Insert " << x << std::endl;
	visualizer->clear();
	visualizer->newStep(root);

	insertVisualize(root, x);

	visualizer->newStep(root);
	
	visualizer->start();
}

void AVL::deleteNode(TreeNode*& node)
{
	if (!node->Child(0) || !node->Child(1)) {
		visualizer->duplicateState();
		visualizer->removeEdgeFromParent(node);
		visualizer->removeNode(node);

		TreeNode* child = node->Child(0);
		if (!child) child = node->Child(1);

		if (child) visualizer->removeEdgeFromParent(child);

		delete node;
		node = child;
		visualizer->reArrange(root);
		return;
	}

	TreeNode* child = node->Child(1);
	if (!child->Child(0)) {
		visualizer->duplicateState();
		visualizer->removeEdgeFromParent(node);
		visualizer->removeEdgeFromParent(child);
		visualizer->removeEdgeFromParent(node->Child(0));
		visualizer->removeNode(node);
		child->Child(0) = node->Child(0);
		delete node;
		node = child;
		visualizer->reArrange(root);
		return;
	}

	std::stack<TreeNode*> st;
	while (child->Child(0)->Child(0)) {
		st.push(child);
		child = child->Child(0);
	}

	TreeNode *replace = child->Child(0);
	visualizer->duplicateState();
	visualizer->highlightNode(replace);

	visualizer->duplicateState();
	visualizer->removeEdgeFromParent(node);
	visualizer->removeEdgeFromParent(replace);
	if (replace->Child(1)) visualizer->removeEdgeFromParent(replace->Child(1));
	visualizer->removeEdgeFromParent(node->Child(0));
	visualizer->removeEdgeFromParent(node->Child(1));
	visualizer->removeNode(node);

	std::cout << "Replace: " << replace->Value() << std::endl;
	child->Child(0) = replace->Child(1);
	replace->Child(0) = node->Child(0);
	replace->Child(1) = node->Child(1);
	delete node;
	node = replace;
	visualizer->reArrange(root);

	while (!st.empty()) {
		balanceVisualize(st.top());
		st.pop();
	}
}

void AVL::deleteVisualize(TreeNode*& node, int x)
{
	if (!node) return;

	visualizer->duplicateState();
	visualizer->highlightNode(node);

	if (node->getValue() == x) {
		deleteNode(node);
		return;
	}
	if (node->Value() > x) {
		if (node->Child(0)) {
			visualizer->duplicateState();
			visualizer->highlightEdge(node, node->Child(0));
		}
		deleteVisualize(node->Child(0), x);
		if (node->Child(0)) {
			visualizer->duplicateState();
			visualizer->highlightEdge(node, node->Child(0), Color::normal);
		}
	}
	else {
		if (node->Child(1)) {
			visualizer->duplicateState();
			visualizer->highlightEdge(node, node->Child(1));
		}
		deleteVisualize(node->Child(1), x);
		if (node->Child(1)) {
			visualizer->duplicateState();
			visualizer->highlightEdge(node, node->Child(1), Color::normal);
		}
	}
	node->update();
	visualizer->duplicateState();
	visualizer->highlightNode(node, Color::normal);
	balanceVisualize(node);
}

void AVL::Delete(int x)
{
	std::cout << "delete " << x << std::endl;

	visualizer->clear();
	visualizer->newStep(root);
	deleteVisualize(root, x);
	visualizer->newStep(root);
	visualizer->start();
}

TreeNode* AVL::searchVisualize(TreeNode*& node, int x)
{
	if (!node) return node;
	if (node->Value() == x) {
		visualizer->duplicateState();
		visualizer->highlightNode(node, Color::found);
		visualizer->duplicateState();
		return node;
	}

	visualizer->duplicateState();
	visualizer->highlightNode(node);

	TreeNode *ret = nullptr;
	if (node->Value() > x) {
		if (node->Child(0)) {
			visualizer->duplicateState();
			visualizer->highlightEdge(node, node->Child(0));
		}
		ret = searchVisualize(node->Child(0), x);
		if (node->Child(0)) {
			visualizer->duplicateState();
			visualizer->highlightEdge(node, node->Child(0), Color::normal);
		}
	}
	else {
		if (node->Child(1)) {
			visualizer->duplicateState();
			visualizer->highlightEdge(node, node->Child(1));
		}
		ret = searchVisualize(node->Child(1), x);
		if (node->Child(1)) {
			visualizer->duplicateState();
			visualizer->highlightEdge(node, node->Child(1), Color::normal);
		}
	}
	visualizer->duplicateState();
	visualizer->highlightNode(node, Color::normal);
	return ret;
}

void AVL::search(int x)
{
	std::cout << "Search " << x << std::endl;
	visualizer->clear();
	visualizer->newStep(root);
	TreeNode *node = searchVisualize(root, x);
	if (node) {
		visualizer->duplicateState();
		visualizer->highlightNode(node, Color::normal);
	}
	visualizer->start();
}
