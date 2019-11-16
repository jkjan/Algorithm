#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> graph[1001]; // n번째 노드와 그와 연결된 노드가 저장된 희소 그래프 
bool visited[1001]; // 노드의 방문 여부를 저장하는 배열 

void dfs(int v);

int main(int argc, char** argv) {
	int V, E; // 노드의 개수, 엣지의 개수 
	int u, v; // 출발 노드, 도착 노드
	int i; // 반복자 
	ifstream fp("../graph_input3.txt");
	fp >> V >> E;
	
	fill_n(visited, 1001, false);
	
	for (i = 0; i < E; i++) { // 그래프의 입력 
		fp >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	dfs(0);
	
	return 0;
}

void dfs(int v) {
	visited[v] = true; // 1. v번째 노드를 방문했음을 표시한다. 
	for (vector<int>::iterator itor = graph[v].begin(); itor != graph[v].end(); ++itor) { // 2. v번째 노드와 연결된 노드 중 
		if (!visited[*itor]) { // 3. 방문한 적이 없는 노드라면, 
			cout << v << " goes to " << *itor << endl; 
			dfs(*itor); // 4. 그 노드에 대해서 위 1 ~ 4 과정을 다시 재귀적으로 반복한다. 
		}
	}
}
