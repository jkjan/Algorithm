#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class edge { // �켱���� ť�� �߰��� ���� Ŭ���� 
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

bool operator < (edge a, edge b) { // �� ������ 
	return a.weight > b.weight;
}

vector< pair<int, int> > graph[1001]; // ��� ��� - ���� ���, �׿� ���� ����� ����Ǵ� �׷��� 
 
vector< pair<int, int> > prim(int V); // ���� �˰����� ����� �Լ� 

int main(int argc, char** argv) {
	int V, E; // ���� ������ ���� 
	int u, v, w; // ��� ���, ���� ���, ����ġ 
	int i; // �ݺ��� 
	ifstream fp("../graph_input.txt");
	fp >> V >> E;
	
	for (i = 0; i < E; i++) { // �׷����� �Է� 
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
	vector<int> nodes; // ������ �߰��� ���� 
	vector< pair<int, int> > mcst; // �ּ� ��� ���� Ʈ�� 

	nodes.push_back(1); // 1. Ư���� ������ ���� �� 1�� ������ �����Ѵ�. 
	
	while (nodes.size() < V) {
		priority_queue<edge> cand; // �ĺ� ������ ����ġ �� �ּҰ��� ������ ������ ��ȯ�ϴ� �켱���� ť 

		for (vector<int>::iterator itor = nodes.begin(); itor != nodes.end(); ++itor) {  // 2. ���� �߰��� ���� 
			for (vector< pair<int, int> >::iterator eitor = graph[*itor].begin(); eitor != graph[*itor].end(); ++eitor) { // 3. ����� ������ Ž���ϸ鼭 
				vector<int>::iterator nitor = find(nodes.begin(), nodes.end(), eitor->first); // 4. �̹� �߰��� ���� ����� ���� �ƴ϶��, 
				if (nitor == nodes.end()) {
					cand.push(edge(*itor, eitor->first, eitor->second)); // 5. �ش� ������ ����ġ�� �켱���� ť�� �߰��Ѵ�. 
				}
			}
		}
		
		if (!cand.empty()) { // 6. ť�� ���� �ʾҴٸ�, �� ���� �߰��� ���� ���� ��带 �����ϴ� ������ �ϳ��� �ִٸ� 
			mcst.push_back(pair<int, int>(cand.top().from, cand.top().to)); // 7. �� ������ �ּ� ��� ���� Ʈ���� �߰��ϰ�, 
		}
		else {
			cout << "no mcst" << endl; // 9. �׷��� �׷� ������ �ϳ��� ������ �ּ� ���� Ʈ���� �ƴϴ�. (������ �׷���) 
			break;
		}
		nodes.push_back(cand.top().to); // 8. ��带 ����Ʈ�� �߰��Ѵ�. 
	}
	
	return mcst;
}

