#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

bool visited[1001];
stack<int> postNumStack;
vector< vector <int> > scc;
int sccCnt = 0;

void dfs(vector<int>* graph, int v, bool reverse);
vector<int>* reverse(vector<int>* graph, int V);
void getSCC(vector<int>* graph, int V);

int main(int argc, char** argv) {
	int V, E;
	int u, v;
	int i;
	ifstream fp("../directed_graph.txt");
	fp >> V >> E;	
	vector<int> graph[1001];

	for (i = 0; i < E; i++) { // 그래프의 입력 
		fp >> u >> v;
		graph[u].push_back(v);
	}	
	
	getSCC(graph, V); // 강한 연결 요소 구하기 
	
	for (i = 0; i < sccCnt; i++) { // 계산된 강한 연결 요소를 출력 
		cout << "scc " << i+1 << " : ";
		for (vector<int>::iterator itor = scc[i].begin(); itor != scc[i].end(); ++itor) {
			cout << *itor << ' ';
		}
		cout << endl;
	}

	return 0;
}

vector<int>* reverse(vector<int>* graph, int V) { // 역방향 그래프를 반환하는 함수 
	vector<int>* reversedGraph = new vector<int>[V+1];
	for(int i = 1; i <= V; i++) {
		for (vector<int>::iterator itor = graph[i].begin(); itor != graph[i].end(); ++itor) {
			reversedGraph[*itor].push_back(i);
		}
	}
	return reversedGraph;
}

void dfs(vector<int>* graph, int v, bool reverse) { 
	visited[v] = true;
	
	if (!reverse) // 4-1. 원본 그래프를 탐색하며 
		scc[sccCnt].push_back(v);  // 강한 연결 요소들에 노드를 추가한다. 
	
	for (vector<int>::iterator itor = graph[v].begin(); itor != graph[v].end(); ++itor) {
		if (!visited[*itor]) {
			dfs(graph, *itor, reverse);
		}
	}
	
	if (reverse) // 2-1. post number 를 구해 정렬하는 방법도 있으나, 이들은 어차피 크기가 작은 순서대로 정해지기 때문에 
		postNumStack.push(v); // stack에 노드를 넣고 pop을 하면 자연스럽게 post number가 가장 큰 노드가 반환된다. 
}

void getSCC(vector<int>* graph, int V) {
	int i;
	int sink;
	
	vector<int>* reversedGraph = reverse(graph, V); // 1. 강한 연결 요소를 구하고자 하는 그래프의 역방향 그래프를 구한다. 
	fill_n(visited, V+1, false);

	for (i = 1; i <= V; i++) { 
		if (!visited[i]) {
			dfs(reversedGraph, i, true); // 2. 구해진 역방향 그래프에서 dfs를 진행하며 post number를 구해 이를 내림차순으로 정렬한다. 
		}
	}

	fill_n(visited, V+1, false);

	while(!postNumStack.empty()) { 
		sink = postNumStack.top(); // 3. 2번에서 구해진 post number에서 가장 큰 값에 해당하는 노드부터 dfs를 진행한다. 
		postNumStack.pop();
		if (!visited[sink]) { // 4. 만약 아직 방문하지 않은 노드라면, 
			scc.push_back(vector<int>()); // 그 노드부터 시작해 dfs를 진행하며 방문한 노드들은 sink에 해당하며,
			dfs(graph, sink, false); //   또다른 강한 연결 요소이다.
			sccCnt++; // 5. 강한 연결 요소의 구분과 출력을 위해 각 요소의 수를 세준다. 
		}
	}
}
