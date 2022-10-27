#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge {
	int to, cost;
};

int N, M;
vector<Edge> bridge[10001];
int st, en;
int maxCost = -2134567890;
int minCost = 2134567890;

void input() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		bridge[from].push_back({ to,cost });
		bridge[to].push_back({ from,cost });
		maxCost = max(maxCost, cost);
		minCost = min(minCost, cost);
	}

	cin >> st >> en;
}

bool bfs(int upperLimit) {
	queue<int> q;

	int visited[10001] = { 0 };
	visited[st] = 1;

	q.push(st);

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		if (now == en) {
			return true;
		}

		for (int i = 0; i < (int)(bridge[now].size()); i++) {

			int next = bridge[now][i].to;

			if (visited[next] == 1)
				continue;

			if (bridge[now][i].cost < upperLimit)
				continue;

			visited[next] = 1;
			q.push(next);
		}
	}

	return false;
}

void solve() {
	int left = minCost;
	int right = maxCost;

	int ans = 0;

	while (left <= right) {
		int mid = (left + right) / 2;

		if (bfs(mid)) {
			ans = mid;
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	cout << ans;
}

int main() {
	input();
	solve();
	return 0;
}