#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

vector<int> graph[1001]; // n���� ��忡 ����� ������ �����ϴ� ��� �׷��� 
bool visited[1001]; // ����� �湮 ���θ� �����ϴ� �迭 

void bfs(int v);

int main(int argc, char** argv) {
	int V, E; // ����� ����, ������ ���� 
	int u, v; // ��� ���, ���� ��� 
	int i; // �ݺ��� 
	ifstream fp("../graph_input3.txt");
	fp >> V >> E;
	
	fill_n(visited, 1001, false);
	
	for (i = 0; i < E; i++) { // �׷����� �Է� 
		fp >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	bfs(0);
	
	return 0;
}

void bfs(int v) {
	queue<int> willVisit; // ������ �湮�ؾ� �� ������ �����ϴ� ť 
	int nowVisit; // ���� �湮�ϰ� �ִ� ��� 
	vector<int>::iterator itor; // int�� ������ �ݺ��� 
	visited[v] = true; // 1. v ��° ��带 �湮�ߴ� ǥ���ϰ�, willVisit�� �ִ´�. 
	willVisit.push(v);
	
	while (!willVisit.empty()) {
		nowVisit = willVisit.front(); // 2. ������ �湮�� ����� ����Ʈ���� �ϳ��� ����. 
		willVisit.pop(); // 3. �׸��� �̴� �ٽ� ���� �ʴ´�. 
		for (itor = graph[nowVisit].begin(); itor != graph[nowVisit].end(); ++itor) { // 4. ���� �湮�ϴ� ���� ����� ��� �߿� 
			if (!visited[*itor]) { // 5. ���� �湮�� ���� ���ٸ� 
				cout << nowVisit << " goes to " << *itor << endl;
				visited[*itor] = true; // 6. �湮�ߴٰ� ǥ���ϰ� 
				willVisit.push(*itor); // 7. ť�� �ش� ��带 �ִ´�. 
			}
		}
	}
}
