#include <iostream>
#include <fstream>
#include <algorithm>

#define INF 1000000000

using namespace std;

void floyd_warshall (int** chart, int V);

int main(int argc, char** argv) {
	int V, E; // ���, ������ �� 
	int from; // ������� ��, �� ��쿣 ������ ����.
	int u, v, w; // ��� ���, ���� ���, ����ġ
	int i, j; // �ݺ��� 
	ifstream fp("../directed_weighted_graph1.txt");
	
	fp >> V >> E;
	fp >> from;
	
	int** distChart = new int*[V+1]; // i��° ������ j��° �������� �Ÿ��� �����ϴ� ǥ 
	
	for (i = 1; i <= V; i++) { // distChart�� �ʱ�ȭ, �Ÿ��� ������ INF�� ���� 
		distChart[i] = new int[V+1];
		fill_n(distChart[i] + 1, V, INF);
		distChart[i][i] = 0;
	}
	
	for (i = 0; i < E; i++) { // �׷����� �Է� 
		fp >> u >> v >> w;
		distChart[u][v] = w;
	}
	
	floyd_warshall(distChart, V);
	
	for (i = 1; i <= V; i++) { // �÷��̵�-���� �˰����� ����� ��� 
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
	for (i = 1; i <= V; i++) { // ��� i�� �߰��ϸ鼭 
		for (j = 1; j <= V; j++) { // ��� j���� 
			for (k = 1; k <= V; k++) { // ��� k�� ���� �� �� 
				chart[j][k] = min(chart[j][k], chart[j][i] + chart[i][k]); // i�� ���ļ�, ��  j���� i����, i���� k���� ���� ���� �� �����ٸ� ���� 
			}
		}
	}
}
