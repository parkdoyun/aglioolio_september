#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
	int to, cost;
	int crossed;
};

bool operator < (Edge A, Edge B) {
	if (A.cost > B.cost)
		return true;
	else
		return false;
}

int n, m, t;
int s, g, h;
vector<Edge> road[2001];
vector<int> candidate;
int visited[2001][2];

void init() {
	for (int i = 0; i < 2001; i++)
		road[i].clear();

	candidate.clear();
}

void input() {
	cin >> n >> m >> t;
	cin >> s >> g >> h;
	for (int i = 0; i < m; i++) {
		int a, b, cost;
		cin >> a >> b >> cost;
		road[a].push_back({ b,cost });
		road[b].push_back({ a,cost });
	}

	for (int i = 0; i < t; i++) {
		int a;
		cin >> a;
		candidate.push_back(a);
	}
}

void dijkstra() {
	priority_queue<Edge> pq;

	for (int i = 1; i <= n; i++) {
		visited[i][0] = 2134567890;
		visited[i][1] = 0;
	}

	visited[s][0] = 0;

	pq.push({ s,0,0});

	while (!pq.empty()) {
		Edge now = pq.top();
		pq.pop();

		if (visited[now.to][0] < now.cost)
			continue;

		for (int i = 0; i < (int)(road[now.to].size()); i++) {
			int next = road[now.to][i].to;

			int nextcost = now.cost + road[now.to][i].cost;

			int nextCrossed = now.crossed;

			if ((now.to == g && next == h) || (now.to == h && next == g)) {
				nextCrossed = 1;
			}

			if (visited[next][0] < nextcost)
				continue;

			if (visited[next][0] == nextcost && visited[next][1] >= nextCrossed)
				continue;

			visited[next][0] = nextcost;
			visited[next][1] = nextCrossed;
			pq.push({ next,nextcost,nextCrossed});
		}
	}
}

void solve() {
	dijkstra();
	sort(candidate.begin(), candidate.end());

	int ans[2001] = { 0 };

	for (int i = 0; i < t; i++) {
		if (visited[candidate[i]][0] != 2134567890 && visited[candidate[i]][1] == 1) {
			ans[i] = 1;
		}
	}

	for (int i = 0; i < (int)(candidate.size()); i++)
		if (ans[i] == 1)
			cout << candidate[i] << " ";

	cout << "\n";
}

int main() {

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		input();
		solve();
	}

	return 0;
}