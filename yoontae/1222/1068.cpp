#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> children[50];
int root;
int erase;
int ans = 0;

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		if (a == -1) {
			root = i;
		}
		else {
			children[a].push_back(i);
		}
	}

	cin >> erase;
}

void dfs(int node) {

	if (children[node].size() == 0) {
		ans++;
		return;
	}

	if (children[node].size() == 1 && children[node][0] == erase) {
		ans++;
		return;
	}

	for (auto m : children[node]) {
		if (m == erase)
			continue;

		dfs(m);
	}
}

void solve() {
	if (erase == root) {
		cout << 0;
		return;
	}


	dfs(root);

	cout << ans;
}

int main() {
	input();
	solve();

	return 0;
}