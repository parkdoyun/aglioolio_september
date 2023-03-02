#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// A가 B에 의존하면 B -> A 방향으로 그래프 만들기

struct Com {
	int num, cost;
};

bool operator<(Com a, Com b) {
	if (a.cost < b.cost) return false;
	if (a.cost > b.cost) return true;
	return false;
}

int T;
int N, D, C;
vector<Com> v[10001];
int dist[10001];
int cnt;
int ans;

void init() {
	for (int i = 0; i < 10001; i++)
		v[i].clear();
	cnt = 0;
	ans = 0;
}

void dijkstra() {
	priority_queue<Com> pq;
	pq.push({ C,0 });

	for (int i = 1; i <= N; i++)
		dist[i] = 2134567890;
	dist[C] = 0;

	while (!pq.empty()) {
		Com now = pq.top();
		pq.pop();

		if (dist[now.num] < now.cost)
			continue;

		for (int i = 0; i < v[now.num].size(); i++) {
			Com next = v[now.num][i];
			int nextCost = dist[now.num] + next.cost;
			if (dist[next.num] <= nextCost)
				continue;
			dist[next.num] = nextCost;
			pq.push({ next.num,nextCost });
		}
	}

	for (int i = 1; i <= N; i++) {
		if (dist[i] != 2134567890) {
			cnt++;
			if (dist[i] > ans)
				ans = dist[i];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();

		cin >> N >> D >> C;
		for (int i = 0; i < D; i++) {
			int to, from, time;
			cin >> to >> from >> time;
			v[from].push_back({ to,time });
		}

		dijkstra();

		cout << cnt << " " << ans << '\n';
	}

	return 0;
}
