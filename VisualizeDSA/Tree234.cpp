#include "Tree234.hpp"

void Tree234::setup(Visualizer* _visualizer)
{
	visualizer = _visualizer;
	visualizer->setTextboxes({ "Build", "Insert", "Delete", "Search" });
	/*visualizer->addTextbox("Build");
	visualizer->addTextbox("Insert");
	visualizer->addTextbox("Delete");
	visualizer->addTextbox("Search");*/
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
		search(Tools::String::toInt(input));
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
		Tools::Tree::killTree(root);
		root = nullptr;
	}
	exist.clear();
	for (int x : values) {
		if (exist.find(x) != exist.end()) continue;
		exist.emplace(x, 1);
		insertBuild(root, x);
	}

	visualizer->layoutTree(root);

	visualizer->clear();
	visualizer->setSource({});
	visualizer->newStep(root);

	visualizer->start();
}

void Tree234::dropVisualize(TreeNode*& node)
{
	visualizer->duplicateState("	extend(cur), merge_to_parent(cur)");
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
	visualizer->duplicateState("if cur has 3 values:");
	if (node->getValueCount() == 3) {
		dropVisualize(node);
	}
	visualizer->duplicateState("if cur has no child: cur->add_value(x), return");
	if (node->getRealChildCount() == 0) {
		std::vector<int> values = node->getValues();
		values.push_back(x);
		std::sort(values.begin(), values.end());
		delete node;
		node = new TreeNode(values);
		visualizer->reArrange(root, 1);
		return;
	}
	int cnt = node->getValueCount();
	for (int i = 0; i <= cnt; i++) {
		if (i < cnt && x == node->getValue(i)) return;
		if (i == cnt || x < node->Value(i)) {
			visualizer->duplicateState("insert(find_child, x)");
			visualizer->highlightEdge(node, node->Child(i));
			visualizer->highlightNode(node->Child(i));
			if (node->Child(i) && node->Child(i)->getValueCount() == 3) {
				visualizer->duplicateState("if cur has 3 values:");
				
				dropVisualize(node->Child(i));
				mergeVisualize(node, i);
				
				visualizer->duplicateState("if cur has no child: cur->add_value(x), return");
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
	if (exist.find(x) != exist.end()) return;

	visualizer->clear();
	visualizer->setSource({
		"if !root: root = new Node({x}), return",
		"if cur has 3 values:",
		"	extend(cur), merge_to_parent(cur)",
		"if cur has no child: cur->add_value(x), return",
		"insert(find_child, x)",
	});
	visualizer->newStep(root, "#");
	visualizer->newStep(root, "if !root: root = new Node({x}), return");
	visualizer->highlightNode(root);
	insertVisualize(root, x);
	visualizer->newStep(root, "#");
	visualizer->start();

}


void Tree234::merge3(TreeNode* node, TreeNode* sibNode, TreeNode* idNode)
{
	sibNode->memorizePosition();
	sibNode->setPosition(node->getPosition());
	idNode->memorizePosition();
	idNode->setPosition(node->getPosition());
	visualizer->reArrange0(root);

	node->addValue(sibNode->getValue(), 0);
	node->addChild(sibNode->Child(0), 0);
	node->Child(1) = sibNode->Child(1);

	node->addValue(idNode->getValue(), 2);
	node->Child(2) = idNode->Child(0);
	node->addChild(idNode->Child(1), 3);

	visualizer->newStep(root);
	visualizer->reArrange(root);

	delete sibNode;
	delete idNode;
}

bool Tree234::fix(TreeNode* node, int id)
{
	int sib = id + 1, valueId = id;
	if (id) sib = id - 1, valueId = id - 1;
	TreeNode *sibNode = node->Child(sib), *idNode = node->Child(id);
	if (idNode->getValueCount() > 1) return false;
	visualizer->duplicateState();
	visualizer->highlightNode(node);
	visualizer->highlightNode(idNode);
	visualizer->highlightNode(sibNode);
	if (node->Child(sib)->getValueCount() > 1) {
		if (sib < id) {
			idNode->addValue(node->getValue(valueId), 0);				
			visualizer->newStep(root);

			node->Value(valueId) = sibNode->getValue(sibNode->getValueCount() - 1);
			node->update();				
			visualizer->newStep(root);

			idNode->addChild(sibNode->Child(sibNode->getValueCount()), 0);
			sibNode->removeChild(sibNode->getValueCount());
			sibNode->removeValue(sibNode->getValueCount() - 1);
		}
		else {
			idNode->addValue(node->getValue(valueId), idNode->getValueCount());

			visualizer->newStep(root);
			node->Value(valueId) = sibNode->getValue(0);
			node->update();

			visualizer->newStep(root);

			idNode->addChild(sibNode->Child(0), idNode->getValueCount());
			sibNode->removeChild(0);
			sibNode->removeValue(0);
		}

		visualizer->newStep(root);
		visualizer->reArrange(root);
	}
	else {
		if (sib > id) {
			std::swap(id, sib);
			idNode = node->Child(id);
			sibNode = node->Child(sib);
		}

		visualizer->layoutTree(root);
		visualizer->newStep(root);

		if (node->getValueCount() == 1) {
			merge3(node, sibNode, idNode);
		}
		else {
			TreeNode* tmp = new TreeNode({ node->getValue(valueId)});
			tmp->Child(0) = node->Child(valueId);
			tmp->Child(1) = node->Child(valueId + 1);
			tmp->setPosition(node->getPosition());
			node->removeValue(valueId);
			node->removeChild(valueId);
			node->Child(valueId) = tmp;

			visualizer->newStep(root);
			visualizer->reArrange(root);

			visualizer->layoutTree(root);
			visualizer->newStep(root);
			merge3(tmp, sibNode, idNode);
		}
	}
	return true;
}

void Tree234::removeValue(TreeNode* node, TreeNode* par)
{
	if (node->getValueCount() > 1) {
		visualizer->duplicateState();
		visualizer->highlightNode(node);
		node->removeValue(0);
		visualizer->newStep(root);
		visualizer->reArrange(root);
	}
}

void Tree234::deleteNodeValue(TreeNode*& node, int id, TreeNode *par)
{
	if (node->getRealChildCount() == 0) {
		if (node->getValueCount() > 1) {
			visualizer->duplicateState();
			visualizer->highlightNode(node);
			node->removeValue(id);
			visualizer->newStep(root);
			visualizer->reArrange(root);
			return;
		}
		removeValue(node, par);
		return;
	}
	int x = node->getValue(id);
	if (fix(node, id + 1)) {
		return deleteVisualize(node, x, par);
	}
	TreeNode* tmp = node->Child(id + 1), *parTmp = node;
	while (tmp->Child(0)) {
		if (fix(tmp, 0)) continue;
		parTmp = tmp;
		tmp = tmp->Child(0);
	}

	visualizer->duplicateState();
	visualizer->highlightNode(node);
	visualizer->highlightNode(tmp);
	node->Value(id) = tmp->Value(0);

	visualizer->layoutTree(root);
	visualizer->newStep(root);
	removeValue(tmp, parTmp);
}

void Tree234::deleteVisualize(TreeNode*& node, int x, TreeNode* par)
{
	if (!node) return;

	for (int i = 0; i < node->getValueCount(); ++i) {
		if (node->getValue(i) == x)
			return deleteNodeValue(node, i, par);
	}
	int i = 0;
	while (true) {
		i = 0;
		while (i < node->getValueCount() && x > node->getValue(i)) ++i;
		if (!fix(node, i)) break;
	}	
	deleteVisualize(node->Child(i), x, node);
}

void Tree234::Delete(int x)
{
	std::cout << "Delete " << x << std::endl;
	if (!root) return;
	if (exist.find(x) == exist.end()) return;
	visualizer->clear();
	visualizer->setSource({
		"node = search for x",
		"if node is not leaf:",
		"	swap value with successor",
		"	node = successor",
		"// now delete value in node",
		"delete x in new node",
		});
	visualizer->newStep(root);

	deleteVisualize(root, x);

	visualizer->start();
}

void Tree234::search(int x)
{
	std::cout << "Search " << x << std::endl;
	if (!root) return;
	visualizer->clear();

	visualizer->setSource({
		"Node *cur = root",
		"while cur != NULL:",
		"	i = 0",
		"	while i < cur->value_count and x > cur->value(i):",
		"		++i",
		"	if i < cur->value_count and x == cur->value(i):",
		"		return cur, i",
		"	cur = cur->child(i)",
		"return not found",
		});

	visualizer->newStep(root);
	visualizer->duplicateState("Node *cur = root");
	visualizer->highlightNode(root);
	visualizer->duplicateState("while cur != NULL:");

	TreeNode* cur = root;
	while (cur) {
		int i = 0;
		visualizer->duplicateState("	i = 0");
		visualizer->duplicateState("	while i < cur->value_count and x > cur->value(i):");
		if (cur->Child(i))
			visualizer->highlightEdge(cur, cur->Child(i));
		while (i < cur->getValueCount() && x > cur->getValue(i)) {
			visualizer->duplicateState("		++i");
			visualizer->duplicateState("	while i < cur->value_count and x > cur->value(i):");
			if (cur->Child(i))
				visualizer->highlightEdge(cur, cur->Child(i), Color::normal);
			++i;
			if (cur->Child(i)) 
				visualizer->highlightEdge(cur, cur->Child(i));
		}
		visualizer->duplicateState("	if i < cur->value_count and x == cur->value(i):");
		if (i < cur->getValueCount() && x == cur->getValue(i)) {
			visualizer->duplicateState("		return cur, i");
			visualizer->highlightNode(cur, Color::found);
			visualizer->newStep(root, "#");
			visualizer->start();
			return;
		}
		visualizer->duplicateState("	cur = cur->child(i)");
		if (cur->Child(i))
			visualizer->highlightEdge(cur, cur->Child(i));
		cur = cur->Child(i);
		visualizer->duplicateState("while cur != NULL:");
		if (cur) visualizer->highlightNode(cur);
	}

	visualizer->newStep(root, "return not found");
	visualizer->duplicateState("#");
	visualizer->start();
}
