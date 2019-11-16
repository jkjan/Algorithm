#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

vector<int> graph[1001]; // n번 노드에 연결된 노드를 저장하는 희소 그래프 
int dfn[1001]; // 노드 별 dfs 로 방문한 순서를 저장하는 배열  
int low[1001]; // depth first search spanning tree에서, 자신의 자식 노드와 최대 1개의 backedge 를 통하여 방문 가능한 최대 dfn 
int dfnc = 0; // dfn에 값을 저장할 때 쓰는 카운터 
stack<int> bcc; // biconnected component, 즉 maximal biconnected subgraph 를 나타내는 스택 

void dfs(int v, int from);

int main(int argc, char** argv) {
	int V, E;
	int u, v;
	int i;
	ifstream fp("../graph_input3.txt");
	fp >> V >> E;
	
	fill_n(dfn, 1001, -1);
	
	for (i = 0; i < E; i++) { // 그래프의 입력 
		fp >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	dfs(1, -1);
	
	return 0;
}

void dfs(int v, int from) {
	dfn[v] = low[v] = dfnc++; // 1. dfn은 단순 dfs에서 자신이 몇 번째로 방문되었는지를 나타내는 변수이다. low는 자기 자신의 dfn과, 
	bcc.push(v);
	
	for (vector<int>::iterator itor = graph[v].begin(); itor != graph[v].end(); ++itor) {
		if (dfn[*itor] < 0) {
			dfs(*itor, v);
			low[v] = low[v] < low[*itor] ? low[v] : low[*itor]; // 2. 자기 자식의 low, 
			
			if (dfn[v] <= low[*itor]) { // 4. dfs의 결과로, 자식의 low가 자신의 dfn보다 크다면, 즉 자식이 자기를 거치지 못하고는 더 위로 갈 방법이 없다면 
				cout << v << " is an articulation point" << endl; // 나는 articulation point, 단절점이다. 
				while (bcc.top() != v) { // 5. 그리고 나를 밟기 전에 방문한 이전의 모든 노드들은 전부 biconnected component이다. 
					cout << bcc.top() << endl;
					bcc.pop();
				}
				cout << endl; 
			}
		}
		else if (*itor != from) {
			low[v] = low[v] < low[*itor] ? low[v] : low[*itor]; // 3. 그리고 자신과 연결된 backedge의 low의 최소값이다. 이때 지금 방문하려는 엣지가 
		}														// 	  backedge인지 아니면 직전 노드가 타고 온 엣지인지 검사한다. 
	}
}
