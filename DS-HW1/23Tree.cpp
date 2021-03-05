#include <iostream>
#include <sstream>
#include <string>
using namespace std;


class TwoThreeNode {
public:	
	TwoThreeNode* parent = nullptr; //parent pointer
	TwoThreeNode* child[4]; // child pointer
	int keys[3]; //current key
	int keyNum = 0; //current keys

	//constructors
	TwoThreeNode(int new_data) {
		resetChild();
		keys[0] = new_data;
		keyNum = 1;
	}
	TwoThreeNode() { 
		resetChild(); 
	}
	TwoThreeNode(TwoThreeNode* p) : parent(p) { resetChild(); }

	//functions
	void resetChild() { 
		for (int i = 0; i <= 3; i++)child[i] = nullptr; 
	}
	void TreeInsert(int new_data) {
		if (child[0] != nullptr) {
			for (int i = 0; i < keyNum; i++) {
				if (new_data < keys[i]) {
					child[i]->TreeInsert(new_data);
					return;
				}
			}
			child[keyNum]->TreeInsert(new_data);
		}
		else {
			NodeInsert(new_data, nullptr);
		}
	}
	void NodeInsert(int new_data, TwoThreeNode* split_node) {
		if (keyNum == 0) {
			keys[0] = new_data;
			child[1] = split_node;
			keyNum = 1;
			return;
		}
		int i;
		for (i = 0; i < keyNum; i++) {
			if (new_data < keys[i]) {
				child[3] = child[2];
				for (int j = 2; j > i; j--) {
					keys[j] = keys[j - 1];
					child[j] = child[j - 1];
				}
				keys[i] = new_data;
				child[i] = child[i + 1];
				child[i + 1] = split_node;
				break;
			}
		}
		if (i == keyNum) {
			keys[i] = new_data;
			child[i + 1] = split_node;
		}
		keyNum++;
		if (keyNum == 3) {
			if (parent == nullptr) {
				parent = new TwoThreeNode;
				parent->child[0] = this;
			}
			parent->split_child(this);
			keyNum /= 2;
		}
	}
	void split_child(TwoThreeNode* full) {
		TwoThreeNode* split = new TwoThreeNode(this);
		int index = 0;
		for (int i = full->keyNum / 2 + 1; i < 3; i++, index++) {
			split->keys[index] = full->keys[i];
			split->child[index] = full->child[i];
			if (split->child[index] != nullptr) {
				split->child[index]->parent = split;
			}
		}
		split->child[index] = full->child[3];
		if (split->child[index] != nullptr) {
			split->child[index]->parent = split;
		}
		split->keyNum = index;
		NodeInsert(full->midVal(), split);
	}
	int& midVal() {
		return keys[keyNum / 2];
	}

	void levelOrder() {
		for (int i = 0; i < keyNum; i++) {
			cout << keys[i] << ((i != keyNum - 1) ? " " : "");
		}
	}
	
	TwoThreeNode* find_root() {
		if (parent == nullptr) return this;
		return parent->find_root();
	}

	int height() {
		if (child[0] == nullptr) return 1;
		return 1 + child[0]->height();
	}

	void deleteAll() {
		if (child[0] != nullptr) {
			for (int i = 0; i <= keyNum; i++) {
				child[i]->deleteAll();
			}
		}
		delete this;
	}

};


class TwoThreeTree {
private:
	TwoThreeNode* root = nullptr;
public:
	~TwoThreeTree() {
		root->deleteAll();
		root = nullptr;
	}
	void insert(int new_data) {
		if (root == nullptr) root = new TwoThreeNode(new_data);
		else {
			root->TreeInsert(new_data);
			root = root->find_root();
		}
	}
	void levelOrder() {
		int H = root->height();
		for (int i = 0; i < H; i++) {
			traversalLayer(root, i, 0);
			cout << endl;
		}
	}
private:
	void traversalLayer(TwoThreeNode* now, int target_layer, int now_layer) {
		if (now == nullptr) return;
		if (target_layer != now_layer) {
			for (int i = 0; i <= now->keyNum; i++) {
				traversalLayer(now->child[i], target_layer, now_layer + 1);
				cout << (i != now->keyNum ? " / " : "");
			}
		}
		else {
			now->levelOrder();
		}
	}

};

int main() {
	string input;
	int data;

	TwoThreeTree tree;
	getline(cin, input);
	stringstream ss(input);
	while (ss >> data) {
		tree.insert(data);
	}
	
	tree.levelOrder(); 
	return 0;
}
