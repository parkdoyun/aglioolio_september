#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
	int num, cost;
};

bool operator < (Edge A, Edge B) {
	if (A.cost < B.cost)
		return false;
	if (A.cost > B.cost)
		return true;
	return false;
}

int n, m, r;
int items[101];
vector<Edge> edge[100];

void input() {
	cin >> n >> m >> r;
	for (int i = 1; i <= n; i++) {
		cin >> items[i];
	}
	for (int i = 0; i < r; i++) {
		int a, b, cost;
		cin >> a >> b >> cost;
		edge[a].push_back({ b,cost });
		edge[b].push_back({ a,cost });
	}
}

int dijkstra(int node) {
	priority_queue<Edge> pq;

	int dist[101] = { 0 };
	for (int i = 1; i <= n; i++) {
		dist[i] = 2134567890;
	}

	dist[node] = 0;

	pq.push({ node,0 });

	while (!pq.empty()) {
		Edge now = pq.top();
		pq.pop();

		if (dist[now.num] < now.cost)
			continue;

		if (now.cost > m)
			continue;

		for (auto m : edge[now.num]) {
			int next = m.num;
			int nextcost = now.cost + m.cost;

			if (dist[next] <= nextcost)
				continue;

			dist[next] = nextcost;
			pq.push({ next, nextcost });
		}
	}

	int itemTot = 0;

	for (int i = 1; i <= n; i++) {
		if (dist[i] <= m) {
			itemTot += items[i];
		}
	}

	return itemTot;
}

void solve() {
	int ans = -1;

	for (int i = 1; i <= n; i++) {
		ans = max(ans, dijkstra(i));
	}

	cout << ans;
}

int main() {
	input();
	solve();

	return 0;
}