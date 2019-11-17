#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

#define INF 100000000

using namespace std;

class edge { // 우선순위 큐에 추가될 엣지 클래스 
	public:
		int to;
		int weight;
		edge(int to, int weight) {
			this->to = to;
			this->weight = weight;
		}
};

bool operator < (edge a, edge b) { // 오름차순 비교 연산자 
	return a.weight > b.weight;
}

int* dijkstra(vector<edge>* graph, int v, int V);

int main(int argc, char** argv) {
	int V, E; // 노드와 엣지의 개수 
	int from; // 최단 거리를 구하는 시작점 
	int u, v, w; // 출발 노드, 도착 노드, 가중치 
	int i; // 반복자 
	ifstream fp("../directed_weighted_graph1.txt");
	
	fp >> V >> E;
	fp >> from;

	vector<edge>* graph = new vector<edge>[V+1];

	for (i = 0; i < E; i++) { // 그래프의 입력 
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
	int* distChart = new int[V+1]; // v번째 노드부터의 거리를 저장할 배열 
	vector<edge>::iterator itor; // edge 를 담는 벡터의 반복자 
	priority_queue<edge> edgePQ; // edge 의 정보를 저장할 우선순위 큐 
	edge shortest(0, 0); // 위의 우선순위 큐에서 꺼낼 엣지 
	
	fill_n(distChart + 1, V, INF); // distChart를 INF로 초기화 
	distChart[v] = 0; // 자기 자신부터 자기 자신까지의 거리는 0 
	edgePQ.push(edge(v, 0)); // 우선순위 큐에 자기 자신을 넣음으로서 시작한다. 
	
	while (!edgePQ.empty()) {
		shortest = edgePQ.top(); // 1. 현재 v가 갈 수 있는 곳 중 가장 빨리 갈 수 있는 노드와 거기까지의 가중치 
		edgePQ.pop();
		
		for (itor = graph[shortest.to].begin(); itor != graph[shortest.to].end(); ++itor) { // 2. 그 중에서 갈 수 있는 다른 노드 중 
			if (distChart[itor->to] > shortest.weight + itor->weight) { // 3. 지금까지 계산된 거리보다 한 단계 거쳐가는 거리가 더 작다면, 
				distChart[itor->to] = shortest.weight + itor->weight; // 4. 거리 표를 수정하고 
				edgePQ.push(edge(itor->to, distChart[itor->to])); // 5. 우선순위 큐에 삽입한다. 
			}
		}
	}
	
	return distChart;
}
