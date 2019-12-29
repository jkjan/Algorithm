#include <iostream>
#include <algorithm>

using namespace std;

class job {
public:
	int num;
	int p;
	int d;
	job() {}
	job(int num, int p, int d) {
		this->num = num;
		this->p = p;
		this->d = d;
	}
};

void input(int n, job* todo);
void swap(int* a, int* b);
int getJ(int n, job* todo, int* J);
bool compare(job a, job b);

int main() {
	int n;
	int cnt;
	cin >> n;

	job* todo = new job[n + 1];
	int* J = new int[n + 1];

	input(n, todo);
	cnt = getJ(n, todo, J);

	for (int i = 1; i <= cnt; i++) {
		cout << todo[J[i]].num << ' ';
	}

	delete[] todo;
	delete[] J;
	return 0;
}

void input(int n, job* todo) {
	int p, d;
	for (int i = 1; i <= n; i++) {
		cin >> p >> d;
		todo[i] = job(i, p, d);
	}
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int getJ(int n, job* todo, int* J) {
	sort(todo + 1, todo + n + 1, compare);
	int y;
	int cnt = 1;
	for (int i = 1; i <= n; i++) {
		y = 1;
		J[cnt] = i;
		while (y < i) {
			if (todo[J[y]].d > todo[J[cnt]].d) {
				swap(J + y, J + cnt);
			}
			y++;
		}
		if (todo[J[cnt]].d >= i)
			cnt++;
	}
	return cnt - 1;
}

bool compare(job a, job b) {
	return a.p > b.p;
}