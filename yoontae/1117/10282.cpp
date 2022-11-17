#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
	int to, cost;
};

bool operator < (Edge A, Edge B) {
	if (A.cost < B.cost)
		return false;
	if (A.cost > B.cost)
		return true;

	return false;
}

int n, d, c;
vector<Edge> connection[10001];
int dist[10001];

void init() {
	for (int i = 0; i <= 10000; i++)
		connection[i].clear();
}

void input() {
	cin >> n >> d >> c;

	for (int i = 0; i < d; i++) {
		int a, b, s;
		cin >> a >> b >> s;
		connection[b].push_back({ a,s });
	}
}

void dijkstra(int st) {
	priority_queue<Edge> pq;

	for (int i = 1; i <= n; i++) {
		dist[i] = 2134567890;
	}

	dist[st] = 0;

	pq.push({ st,0 });

	while (!pq.empty()) {
		Edge now = pq.top();
		pq.pop();

		if (dist[now.to] < now.cost)
			continue;

		for (int i = 0; i < (int)(connection[now.to].size()); i++) {
			Edge next = connection[now.to][i];
			int nextcost = dist[now.to] + next.cost;

			if (dist[next.to] <= nextcost)
				continue;

			dist[next.to] = nextcost;
			pq.push({ next.to, nextcost });
		}
	}
}

void solve() {
	dijkstra(c);

	int ans_cnt = 0;
	int ans_time = 0;

	for (int i = 1; i <= n; i++) {
		if (dist[i] != 2134567890) {
			ans_cnt++;
			ans_time = max(ans_time, dist[i]);
		}
	}

	cout << ans_cnt << " " << ans_time << "\n";
}

int main() {
	int T;
	cin >> T;

	for (int tc = 0; tc < T; tc++) {
		init();
		input();
		solve();
	}

	return 0;
}