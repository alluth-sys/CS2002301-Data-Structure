#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#define INFINITY 0x3f3f3f3f 

class Node {
public:
	void createNode(string n, int w) {
		name = n;
		cost = w;
	}
	bool notCreated() { return !name.size(); }
	void chain(Node* target, int weight) { neighbor.push_back(make_pair(target, weight)); }

	string name = "";
	vector<pair<Node*, int>> neighbor;
	int cost;
	bool isTraversed = false;
	Node* parent = nullptr;
};

//if node exist in graph return the node
Node* find_node_ptr(Node* all, string name, int total) {
	for (int i = 0; i < total; i++) {
		if (all[i].name == name) {
			return &all[i];
		}
	}
	return nullptr;
}

//initialize Node
Node* initNode(Node* graph, string name, int total) {
	for (int i = 0; i < total; i++) {
		if (graph[i].notCreated()) {
			graph[i].createNode(name, 0);
			return &graph[i];
		}
	}
}

void print_path(Node* now) {
	if (now->parent == nullptr) {
		cout << now->name;
		return;
	}
	print_path(now->parent);
	cout << ' ' << now->name;
}

Node* Dijkstra(Node* graph, string start_node, string end_node, int node_num) {
	Node* start_ptr = find_node_ptr(graph, start_node, node_num);
	Node* end_ptr = find_node_ptr(graph, end_node, node_num);
	Node* now_ptr = start_ptr;
	vector<Node*> next_posible;
	while (true) {
		now_ptr->isTraversed = true;
		for (auto i : now_ptr->neighbor) {
			if (i.first->isTraversed) continue;
			if (find(next_posible.begin(), next_posible.end(), i.first) != next_posible.end()) {
				if (i.first->cost > (now_ptr->cost + i.second)) {
					i.first->cost = (now_ptr->cost + i.second);
					i.first->parent = now_ptr;
				}
			}
			else {
				next_posible.push_back(i.first);
				i.first->cost = now_ptr->cost + i.second;
				i.first->parent = now_ptr;
			}
		}
		if (next_posible.empty()) break;

		int min_weight = INFINITY;
		for (auto i : next_posible) {
			if (i->cost < min_weight) {
				now_ptr = i;
				min_weight = i->cost;
			}
		}
		next_posible.erase(find(next_posible.begin(), next_posible.end(), now_ptr));
	}
	return end_ptr;
}

int main() {

	//input
	int node_num, edge_num;
	string start_node, end_node;
	cin >> node_num >> edge_num >> start_node >> end_node;

	//initialize graph
	Node* graph = new Node[node_num];
	for (int i = 0; i < edge_num; ++i) {
		string src, target;
		int w;
		cin >> src >> target >> w;

		//if srcPtr hasn't been created initialize new node
		Node* srcPtr = find_node_ptr(graph, src, node_num);
		if (!srcPtr) { srcPtr = initNode(graph, src, node_num); }

		//if targetPtr hasn't been created initialize new node
		Node* targetPtr = find_node_ptr(graph, target, node_num);
		if (!targetPtr) targetPtr = initNode(graph, target, node_num);

		//chain src to target
		srcPtr->chain(targetPtr, w);
	}

	//Process
	Node* endPtr = Dijkstra(graph, start_node, end_node, node_num);

	//Output
	print_path(endPtr);
	cout << endl << endPtr->cost;
	return 0;
}
