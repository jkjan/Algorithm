#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> graph[1001]; // n��° ���� �׿� ����� ��尡 ����� ��� �׷��� 
bool visited[1001]; // ����� �湮 ���θ� �����ϴ� �迭 

void dfs(int v);

int main(int argc, char** argv) {
	int V, E; // ����� ����, ������ ���� 
	int u, v, w; // ��� ���, ���� ���, ����ġ. ��, ����ġ�� �� ��쿣 ������ �ʴ´�. 
	int i; // �ݺ��� 
	ifstream fp("../graph_input.txt");
	fp >> V >> E;
	
	fill_n(visited, 1001, false);
	
	for (i = 0; i < E; i++) { // �׷����� �Է� 
		fp >> u >> v >> w;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	dfs(1);
	
	return 0;
}

void dfs(int v) {
	visited[v] = true; // 1. v��° ��带 �湮������ ǥ���Ѵ�. 
	for (vector<int>::iterator itor = graph[v].begin(); itor != graph[v].end(); ++itor) { // 2. v��° ���� ����� ��� �� 
		if (!visited[*itor]) { // 3. �湮�� ���� ���� �����, 
			cout << v << " goes to " << *itor << endl; 
			dfs(*itor); // 4. �� ��忡 ���ؼ� �� 1 ~ 4 ������ �ٽ� ��������� �ݺ��Ѵ�. 
		}
	}
}
