#include<iostream>

using namespace std;


int parent[500001] = { 0, };


int Find(int now) {
	
	if (now == parent[now]) {
		return now;
	}
	return parent[now] = Find(parent[now]);


	
}


void Union(int A, int B) {
	
		int pA = Find(A);
		int pB = Find(B);
		if (pA == pB)
			return;
		parent[pB] = pA;
	
}


int n, m;
int ans = 0;
bool cycle = false;
void input() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		parent[i] = i;
	}
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		if (Find(a) == Find(b)) {
			if (!cycle) {
				ans = i;
				cycle = true;
			}
		}
		Union(a, b);

	}
}
int main() {
	input();

	cout << ans;

}
