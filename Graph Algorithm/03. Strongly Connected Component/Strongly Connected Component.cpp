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

	for (i = 0; i < E; i++) { // �׷����� �Է� 
		fp >> u >> v;
		graph[u].push_back(v);
	}	
	
	getSCC(graph, V); // ���� ���� ��� ���ϱ� 
	
	for (i = 0; i < sccCnt; i++) { // ���� ���� ���� ��Ҹ� ��� 
		cout << "scc " << i+1 << " : ";
		for (vector<int>::iterator itor = scc[i].begin(); itor != scc[i].end(); ++itor) {
			cout << *itor << ' ';
		}
		cout << endl;
	}

	return 0;
}

vector<int>* reverse(vector<int>* graph, int V) { // ������ �׷����� ��ȯ�ϴ� �Լ� 
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
	
	if (!reverse) // 4-1. ���� �׷����� Ž���ϸ� 
		scc[sccCnt].push_back(v);  // ���� ���� ��ҵ鿡 ��带 �߰��Ѵ�. 
	
	for (vector<int>::iterator itor = graph[v].begin(); itor != graph[v].end(); ++itor) {
		if (!visited[*itor]) {
			dfs(graph, *itor, reverse);
		}
	}
	
	if (reverse) // 2-1. post number �� ���� �����ϴ� ����� ������, �̵��� ������ ũ�Ⱑ ���� ������� �������� ������ 
		postNumStack.push(v); // stack�� ��带 �ְ� pop�� �ϸ� �ڿ������� post number�� ���� ū ��尡 ��ȯ�ȴ�. 
}

void getSCC(vector<int>* graph, int V) {
	int i;
	int sink;
	
	vector<int>* reversedGraph = reverse(graph, V); // 1. ���� ���� ��Ҹ� ���ϰ��� �ϴ� �׷����� ������ �׷����� ���Ѵ�. 
	fill_n(visited, V+1, false);

	for (i = 1; i <= V; i++) { 
		if (!visited[i]) {
			dfs(reversedGraph, i, true); // 2. ������ ������ �׷������� dfs�� �����ϸ� post number�� ���� �̸� ������������ �����Ѵ�. 
		}
	}

	fill_n(visited, V+1, false);

	while(!postNumStack.empty()) { 
		sink = postNumStack.top(); // 3. 2������ ������ post number���� ���� ū ���� �ش��ϴ� ������ dfs�� �����Ѵ�. 
		postNumStack.pop();
		if (!visited[sink]) { // 4. ���� ���� �湮���� ���� �����, 
			scc.push_back(vector<int>()); // �� ������ ������ dfs�� �����ϸ� �湮�� ������ sink�� �ش��ϸ�,
			dfs(graph, sink, false); //   �Ǵٸ� ���� ���� ����̴�.
			sccCnt++; // 5. ���� ���� ����� ���а� ����� ���� �� ����� ���� ���ش�. 
		}
	}
}
