#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

class edge { // 엣지에 대한 정보를 담은 클래스 
public:
	int node1; // 출발 노드 
	int node2; // 도착 노드 
	int weight; // 가중치 
	edge(int a, int b, int w) { // 생성자 
		this->node1 = a;
		this->node2 = b;	
		this->weight = w;
	}
};

bool operator < (edge a, edge b) { // 오름차순 비교 연산자 
	return a.weight > b.weight;
}

int label[1001]; // 노드의 라벨 

vector< pair<int, int> > kruskal (priority_queue<edge> edges, int V);

int main(int argc, char** argv) {
	int V, E; // 노드, 엣지의 개수 
	int u, v, w; // 출발 노드, 도착 노드, 가중치
	priority_queue<edge> edges; // 엣지가 저장되는 우선순위 큐
	int i; // 반복자 
		 
	ifstream fp("../graph_input.txt"); 
	fp >> V >> E;
	 
	for (i = 1; i <= V; i++) { // 노드들의 라벨링 
		label[i] = i;
	}
	 
	for (i = 0; i < E; i++) { // 그래프의 입력 
		fp >> u >> v >> w;
		edges.push(edge(u, v, w)); // 우선순위 큐에 엣지를 추가 
	}
	
	vector< pair<int, int> > mcst = kruskal(edges, V);
	
	for (vector< pair<int, int> >::iterator itor = mcst.begin(); itor != mcst.end(); ++itor) {
		printf("%c %c\n", itor->first + 64, itor->second + 64);
	} 
	
	fp.close();
	return 0;
}

vector< pair<int, int> > kruskal (priority_queue<edge> edges, int V) {
	vector< pair<int, int> > mcst; // minimum cost spanning tree, 최소 비용 신장 트리 
	int i; // 반복자 
	edge a(0, 0, 0);
	int change;
	
	while(!edges.empty()) { 
		a = edges.top();
		edges.pop();
		
		if (label[a.node1] != label[a.node2]) { // 같은 라벨의 노드가 아니라면 
			mcst.push_back(pair<int, int>(a.node1, a.node2)); // 엣지를 추가하고 
			change = label[a.node2];
			
			for (i = 1; i <= V; i++) { // 라벨을 같게 하여 union 작업을 진행한다 
				if (label[i] == change)
					label[i] = label[a.node1];
			}
		}
	}
	
	if (mcst.size() != V-1) // 만들어진 트리의 엣지가 노드 - 1 개가 아니면 이는 최소 비용 신장 트리가 아니다 
		cout << "no mcst" << endl;
	
	return mcst;
} 
