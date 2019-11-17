#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

#define INF 100000000

using namespace std;

class edge { // �켱���� ť�� �߰��� ���� Ŭ���� 
	public:
		int to;
		int weight;
		edge(int to, int weight) {
			this->to = to;
			this->weight = weight;
		}
};

bool operator < (edge a, edge b) { // �������� �� ������ 
	return a.weight > b.weight;
}

int* dijkstra(vector<edge>* graph, int v, int V);

int main(int argc, char** argv) {
	int V, E; // ���� ������ ���� 
	int from; // �ִ� �Ÿ��� ���ϴ� ������ 
	int u, v, w; // ��� ���, ���� ���, ����ġ 
	int i; // �ݺ��� 
	ifstream fp("../directed_weighted_graph1.txt");
	
	fp >> V >> E;
	fp >> from;

	vector<edge>* graph = new vector<edge>[V+1];

	for (i = 0; i < E; i++) { // �׷����� �Է� 
		fp >> u >> v >> w;
		graph[u].push_back(edge(v, w));
	}
	
	int* distChart = dijkstra(graph, from, V);
	
	for (i = 1; i <= V; i++) {
		if (distChart[i] != INF)
			cout << distChart[i];
		else
			cout << "INF";
		cout << ' ';
	}
	
	delete[] distChart;
	delete[] graph;
	return 0;
}

int* dijkstra(vector<edge>* graph, int v, int V) {
	int* distChart = new int[V+1]; // v��° �������� �Ÿ��� ������ �迭 
	vector<edge>::iterator itor; // edge �� ��� ������ �ݺ��� 
	priority_queue<edge> edgePQ; // edge �� ������ ������ �켱���� ť 
	edge shortest(0, 0); // ���� �켱���� ť���� ���� ���� 
	
	fill_n(distChart + 1, V, INF); // distChart�� INF�� �ʱ�ȭ 
	distChart[v] = 0; // �ڱ� �ڽź��� �ڱ� �ڽű����� �Ÿ��� 0 
	edgePQ.push(edge(v, 0)); // �켱���� ť�� �ڱ� �ڽ��� �������μ� �����Ѵ�. 
	
	while (!edgePQ.empty()) {
		shortest = edgePQ.top(); // 1. ���� v�� �� �� �ִ� �� �� ���� ���� �� �� �ִ� ���� �ű������ ����ġ 
		edgePQ.pop();
		
		for (itor = graph[shortest.to].begin(); itor != graph[shortest.to].end(); ++itor) { // 2. �� �߿��� �� �� �ִ� �ٸ� ��� �� 
			if (distChart[itor->to] > shortest.weight + itor->weight) { // 3. ���ݱ��� ���� �Ÿ����� �� �ܰ� ���İ��� �Ÿ��� �� �۴ٸ�, 
				distChart[itor->to] = shortest.weight + itor->weight; // 4. �Ÿ� ǥ�� �����ϰ� 
				edgePQ.push(edge(itor->to, distChart[itor->to])); // 5. �켱���� ť�� �����Ѵ�. 
			}
		}
	}
	
	return distChart;
}
