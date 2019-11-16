#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

class edge { // ������ ���� ������ ���� Ŭ���� 
public:
	int node1; // ��� ��� 
	int node2; // ���� ��� 
	int weight; // ����ġ 
	edge(int a, int b, int w) { // ������ 
		this->node1 = a;
		this->node2 = b;	
		this->weight = w;
	}
};

bool operator < (edge a, edge b) { // �������� �� ������ 
	return a.weight > b.weight;
}

int label[1001]; // ����� �� 

vector< pair<int, int> > kruskal (priority_queue<edge> edges, int V);

int main(int argc, char** argv) {
	int V, E; // ���, ������ ���� 
	int u, v, w; // ��� ���, ���� ���, ����ġ
	priority_queue<edge> edges; // ������ ����Ǵ� �켱���� ť
	int i; // �ݺ��� 
		 
	ifstream fp("../graph_input.txt"); 
	fp >> V >> E;
	 
	for (i = 1; i <= V; i++) { // ������ �󺧸� 
		label[i] = i;
	}
	 
	for (i = 0; i < E; i++) { // �׷����� �Է� 
		fp >> u >> v >> w;
		edges.push(edge(u, v, w)); // �켱���� ť�� ������ �߰� 
	}
	
	vector< pair<int, int> > mcst = kruskal(edges, V);
	
	for (vector< pair<int, int> >::iterator itor = mcst.begin(); itor != mcst.end(); ++itor) {
		printf("%c %c\n", itor->first + 64, itor->second + 64);
	} 
	
	fp.close();
	return 0;
}

vector< pair<int, int> > kruskal (priority_queue<edge> edges, int V) {
	vector< pair<int, int> > mcst; // minimum cost spanning tree, �ּ� ��� ���� Ʈ�� 
	int i; // �ݺ��� 
	edge a(0, 0, 0);
	int change;
	
	while(!edges.empty()) { 
		a = edges.top();
		edges.pop();
		
		if (label[a.node1] != label[a.node2]) { // ���� ���� ��尡 �ƴ϶�� 
			mcst.push_back(pair<int, int>(a.node1, a.node2)); // ������ �߰��ϰ� 
			change = label[a.node2];
			
			for (i = 1; i <= V; i++) { // ���� ���� �Ͽ� union �۾��� �����Ѵ� 
				if (label[i] == change)
					label[i] = label[a.node1];
			}
		}
	}
	
	if (mcst.size() != V-1) // ������� Ʈ���� ������ ��� - 1 ���� �ƴϸ� �̴� �ּ� ��� ���� Ʈ���� �ƴϴ� 
		cout << "no mcst" << endl;
	
	return mcst;
} 
