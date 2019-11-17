#include <iostream>
#include <fstream>
#include <algorithm>

#define INF 1000000000

using namespace std;

void floyd_warshall (int** chart, int V);

int main(int argc, char** argv) {
	int V, E; // 노드, 엣지의 수 
	int from; // 출발점의 수, 이 경우엔 쓰이지 않음.
	int u, v, w; // 출발 노드, 도착 노드, 가중치
	int i, j; // 반복자 
	ifstream fp("../directed_weighted_graph1.txt");
	
	fp >> V >> E;
	fp >> from;
	
	int** distChart = new int*[V+1]; // i번째 노드부터 j번째 노드까지의 거리를 저장하는 표 
	
	for (i = 1; i <= V; i++) { // distChart의 초기화, 거리가 없으면 INF로 저장 
		distChart[i] = new int[V+1];
		fill_n(distChart[i] + 1, V, INF);
		distChart[i][i] = 0;
	}
	
	for (i = 0; i < E; i++) { // 그래프의 입력 
		fp >> u >> v >> w;
		distChart[u][v] = w;
	}
	
	floyd_warshall(distChart, V);
	
	for (i = 1; i <= V; i++) { // 플로이드-워셜 알고리즘의 결과값 출력 
		for (j = 1; j <= V; j++) {
			if (distChart[i][j] < INF)
				cout << distChart[i][j] << ' ';
			else
				cout << "INF" << ' ';
		}
		cout << endl;
	}
	
	delete[] distChart;
	fp.close();
	return 0;
}

void floyd_warshall (int** chart, int V) {
	int i, j, k;
	for (i = 1; i <= V; i++) { // 노드 i를 추가하면서 
		for (j = 1; j <= V; j++) { // 노드 j에서 
			for (k = 1; k <= V; k++) { // 노드 k로 가는 길 중 
				chart[j][k] = min(chart[j][k], chart[j][i] + chart[i][k]); // i를 거쳐서, 즉  j부터 i까지, i부터 k까지 가는 길이 더 빠르다면 수정 
			}
		}
	}
}
