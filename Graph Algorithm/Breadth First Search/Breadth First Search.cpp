#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

vector<int> graph[1001]; // n번쨰 노드에 연결된 노드들을 저장하는 희소 그래프 
bool visited[1001]; // 노드의 방문 여부를 저장하는 배열 

void bfs(int v);

int main(int argc, char** argv) {
	int V, E; // 노드의 개수, 엣지의 개수 
	int u, v; // 출발 노드, 현재 노드 
	int i; // 반복자 
	ifstream fp("../graph_input3.txt");
	fp >> V >> E;
	
	fill_n(visited, 1001, false);
	
	for (i = 0; i < E; i++) { // 그래프의 입력 
		fp >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	bfs(0);
	
	return 0;
}

void bfs(int v) {
	queue<int> willVisit; // 앞으로 방문해야 할 노드들을 저장하는 큐 
	int nowVisit; // 현재 방문하고 있는 노드 
	vector<int>::iterator itor; // int형 벡터의 반복자 
	visited[v] = true; // 1. v 번째 노드를 방문했다 표시하고, willVisit에 넣는다. 
	willVisit.push(v);
	
	while (!willVisit.empty()) {
		nowVisit = willVisit.front(); // 2. 앞으로 방문할 노드의 리스트에서 하나를 뺀다. 
		willVisit.pop(); // 3. 그리고 이는 다시 들어가지 않는다. 
		for (itor = graph[nowVisit].begin(); itor != graph[nowVisit].end(); ++itor) { // 4. 지금 방문하는 노드와 연결된 노드 중에 
			if (!visited[*itor]) { // 5. 아직 방문한 적이 없다면 
				cout << nowVisit << " goes to " << *itor << endl;
				visited[*itor] = true; // 6. 방문했다고 표시하고 
				willVisit.push(*itor); // 7. 큐에 해당 노드를 넣는다. 
			}
		}
	}
}
