#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class edge { // 우선순위 큐에 추가될 엣지 클래스 
	public:
		int from;
		int to;
		int weight;
		
		edge(int from, int to, int weight) {
			this->from = from;
			this->to = to;
			this->weight = weight;
		}
};

bool operator < (edge a, edge b) { // 비교 연산자 
	return a.weight > b.weight;
}

vector< pair<int, int> > graph[1001]; // 출발 노드 - 도착 노드, 그에 대한 비용이 저장되는 그래프 
 
vector< pair<int, int> > prim(int V); // 프림 알고리즘을 사용할 함수 

int main(int argc, char** argv) {
	int V, E; // 노드와 엣지의 개수 
	int u, v, w; // 출발 노드, 도착 노드, 가중치 
	int i; // 반복자 
	ifstream fp("../graph_input.txt");
	fp >> V >> E;
	
	for (i = 0; i < E; i++) { // 그래프의 입력 
		fp >> u >> v >> w;
		graph[u].push_back(pair<int, int>(v, w));
		graph[v].push_back(pair<int, int>(u, w));
	}
	
	vector< pair<int, int> > mcst = prim(V);
	
	for (i = 0; i < mcst.size(); i++) {
		printf("%c %c\n", mcst[i].first + 64, mcst[i].second + 64);
	}
	
	return 0;
}

vector< pair<int, int> > prim(int V) {
	vector<int> nodes; // 노드들이 추가될 벡터 
	vector< pair<int, int> > mcst; // 최소 비용 신장 트리 

	nodes.push_back(1); // 1. 특별한 조건이 없는 한 1번 노드부터 시작한다. 
	
	while (nodes.size() < V) {
		priority_queue<edge> cand; // 후보 엣지의 가중치 중 최소값을 가지는 엣지를 반환하는 우선순위 큐 

		for (vector<int>::iterator itor = nodes.begin(); itor != nodes.end(); ++itor) {  // 2. 현재 추가된 노드와 
			for (vector< pair<int, int> >::iterator eitor = graph[*itor].begin(); eitor != graph[*itor].end(); ++eitor) { // 3. 연결된 엣지를 탐색하면서 
				vector<int>::iterator nitor = find(nodes.begin(), nodes.end(), eitor->first); // 4. 이미 추가된 노드와 연결된 것이 아니라면, 
				if (nitor == nodes.end()) {
					cand.push(edge(*itor, eitor->first, eitor->second)); // 5. 해당 엣지와 가중치를 우선순위 큐에 추가한다. 
				}
			}
		}
		
		if (!cand.empty()) { // 6. 큐가 비지 않았다면, 즉 새로 추가할 노드와 현재 노드를 연결하는 엣지가 하나라도 있다면 
			mcst.push_back(pair<int, int>(cand.top().from, cand.top().to)); // 7. 그 엣지를 최소 비용 신장 트리에 추가하고, 
		}
		else {
			cout << "no mcst" << endl; // 9. 그러나 그런 엣지가 하나라도 없으면 최소 신장 트리가 아니다. (단절된 그래프) 
			break;
		}
		nodes.push_back(cand.top().to); // 8. 노드를 리스트에 추가한다. 
	}
	
	return mcst;
}

