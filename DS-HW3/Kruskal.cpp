#include <math.h>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
using namespace std;

class Edge {
public:
	int src, dest;
	float probability;
	Edge(int src_, int dest_, float probability_) {
		src = src_;
		dest = dest_;
		probability = probability_;
	}
};

class subset {
public:
	int parent;
	int rank;
};

bool myComp(const Edge& a, const Edge& b) {
	return a.probability > b.probability;
}

int find(int i, map<int, subset>& subsets) {
	if (subsets[i].parent != i) {
		subsets[i].parent = find(subsets[i].parent, subsets);
	}

	return subsets[i].parent;
}

void connectNode(map<int, subset>& subsets, int x, int y) {
	int xroot = find(x, subsets);
	int yroot = find(y, subsets);

	if (subsets[xroot].rank < subsets[yroot].rank) {
		subsets[xroot].parent = yroot;
	}
	else if (subsets[xroot].rank > subsets[yroot].rank) {
		subsets[yroot].parent = xroot;
	}
	else {
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

void Kruskal(vector<Edge>edges, set<int>nodes, int edgeNum) {
	map<int, subset> subsets;
	vector<Edge> result;

	for (const auto& i : nodes) {
		subsets[i].parent = i;
		subsets[i].rank = 0;
	}

	for (unsigned t = 0; t < edges.size(); ++t) {
		Edge e = edges[t];

		int x = find(e.src, subsets);
		int y = find(e.dest, subsets);

		if (x != y) {
			result.push_back(e);
			connectNode(subsets, x, y);
		}
	}

	double p = 1.0;
	if (edgeNum == 1) {
		p = edges.back().probability;
	}
	else {
		for (const auto& i : result) {
			p *= i.probability;
		}
	}

	if (p < 0.05) {
		p = 0.0;
	}

	cout << round(p * 10000.0) / 10000.0 << endl;
}

int main() {
	int paths;
	int node1, node2;
	float probability;

	cin >> paths;

	vector<Edge> edges;
	set<int>nodes;
	for (int i = 0; i < paths; ++i) {
		int node1, node2;
		float prob;
		cin >> node1 >> node2 >> prob;
		nodes.insert(node1);
		nodes.insert(node2);
		Edge t(node1, node2, prob);
		edges.push_back(t);
	}

	//sort edges according to probabilty if there are V nodes then only V-1 nodes are required to build MST
	sort(edges.begin(), edges.end(), myComp);

	//Kruskal algorithm
	Kruskal(edges, nodes, paths);
}
