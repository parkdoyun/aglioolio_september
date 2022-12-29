#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;

int N, M;
int parent[500000];

int Find(int now) {
	if (parent[now] == now)
		return now;
	return parent[now] = Find(parent[now]);
}

void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);
	if (pa == pb) return;
	parent[pb] = pa;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;

	for (int i = 0; i < N; i++)
		parent[i] = i;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		
		// ** 부모가 같으면 사이클 형성 **
		if (Find(a) == Find(b)) {
			cout << i + 1;
			return 0;
		}
		else
			Union(a, b);
	}

	cout << 0;

	return 0;
}
