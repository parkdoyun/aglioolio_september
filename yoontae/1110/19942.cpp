#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int MAP[15][5];
int need[4];
int now[4];
int price;
int minPrice = 2134567890;
vector<int> path;
vector<int> ans;

void input() {
	cin >> N;

	for (int i = 0; i < 4; i++) {
		cin >> need[i];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> MAP[i][j];
		}
	}
}

void dfs(int level) {

	if (level == N) {
		bool flag = true;
		for (int i = 0; i < 4; i++) {
			if (now[i] < need[i])
				flag = false;
		}
		if (flag && price < minPrice) {
			minPrice = price;
			ans = path;
		}
		else if (flag && price == minPrice && path < ans) {
			minPrice = price;
			ans = path;
		}
		return;
	}

	for (int i = 0; i < 2; i++) {
		if (i == 1) {
			dfs(level + 1);
		}
		else {
			for (int i = 0; i < 4; i++) {
				now[i] += MAP[level][i];
			}
			price += MAP[level][4];
			path.push_back(level);
			dfs(level + 1);
			for (int i = 0; i < 4; i++) {
				now[i] -= MAP[level][i];
			}
			price -= MAP[level][4];
			path.pop_back();
		}
	}
}

void solve() {
	dfs(0);

	if (minPrice != 2134567890) {
		cout << minPrice << "\n";
		for (int i = 0; i < (int)(ans.size()); i++) {
			cout << ans[i] + 1 << " ";
		}
	}
	else
		cout << -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	input();
	solve();

	return 0;
}