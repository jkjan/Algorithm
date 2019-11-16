#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

vector<int> graph[1001]; // n�� ��忡 ����� ��带 �����ϴ� ��� �׷��� 
int dfn[1001]; // ��� �� dfs �� �湮�� ������ �����ϴ� �迭  
int low[1001]; // depth first search spanning tree����, �ڽ��� �ڽ� ���� �ִ� 1���� backedge �� ���Ͽ� �湮 ������ �ִ� dfn 
int dfnc = 0; // dfn�� ���� ������ �� ���� ī���� 
stack<int> bcc; // biconnected component, �� maximal biconnected subgraph �� ��Ÿ���� ���� 

void dfs(int v, int from);

int main(int argc, char** argv) {
	int V, E;
	int u, v;
	int i;
	ifstream fp("../graph_input3.txt");
	fp >> V >> E;
	
	fill_n(dfn, 1001, -1);
	
	for (i = 0; i < E; i++) { // �׷����� �Է� 
		fp >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	dfs(1, -1);
	
	return 0;
}

void dfs(int v, int from) {
	dfn[v] = low[v] = dfnc++; // 1. dfn�� �ܼ� dfs���� �ڽ��� �� ��°�� �湮�Ǿ������� ��Ÿ���� �����̴�. low�� �ڱ� �ڽ��� dfn��, 
	bcc.push(v);
	
	for (vector<int>::iterator itor = graph[v].begin(); itor != graph[v].end(); ++itor) {
		if (dfn[*itor] < 0) {
			dfs(*itor, v);
			low[v] = low[v] < low[*itor] ? low[v] : low[*itor]; // 2. �ڱ� �ڽ��� low, 
			
			if (dfn[v] <= low[*itor]) { // 4. dfs�� �����, �ڽ��� low�� �ڽ��� dfn���� ũ�ٸ�, �� �ڽ��� �ڱ⸦ ��ġ�� ���ϰ�� �� ���� �� ����� ���ٸ� 
				cout << v << " is an articulation point" << endl; // ���� articulation point, �������̴�. 
				while (bcc.top() != v) { // 5. �׸��� ���� ��� ���� �湮�� ������ ��� ������ ���� biconnected component�̴�. 
					cout << bcc.top() << endl;
					bcc.pop();
				}
				cout << endl; 
			}
		}
		else if (*itor != from) {
			low[v] = low[v] < low[*itor] ? low[v] : low[*itor]; // 3. �׸��� �ڽŰ� ����� backedge�� low�� �ּҰ��̴�. �̶� ���� �湮�Ϸ��� ������ 
		}														// 	  backedge���� �ƴϸ� ���� ��尡 Ÿ�� �� �������� �˻��Ѵ�. 
	}
}
