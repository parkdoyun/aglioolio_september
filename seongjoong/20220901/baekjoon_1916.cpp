#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
	int num, cost;
};

bool operator<(Edge a, Edge b) {
	// cost 작은 순 -> MINHEAP --> false
	if (a.cost < b.cost) return false;
	if (a.cost > b.cost) return true;
	return false;
}

int N, M;
vector<Edge> v[1001];
int st, en;

priority_queue<Edge> pq;
int dist[1001]; // 해당 도시까지 최단거리

void dijkstra(int now) {
	pq.push({ now,0 });

	for (int i = 1; i <= N; i++)
		dist[i] = 2134567890;
	dist[now] = 0;

	while (!pq.empty()) {
		Edge now = pq.top();
		pq.pop();

		if (dist[now.num] < now.cost)
			continue;

		for (int i = 0; i < v[now.num].size(); i++) {
			Edge next = v[now.num][i];

			int nextCost = dist[now.num] + next.cost;
			// 현재까지 기록된 최소값보다 크거나 같으면 패스
			if (dist[next.num] <= nextCost)
				continue;
			dist[next.num] = nextCost;
			pq.push({ next.num,nextCost });
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		v[from].push_back({ to,cost });
	}
	cin >> st >> en;

	// 가중치가 있는 그래프 최소비용 -> Dijkstra
	dijkstra(st);
	cout << dist[en];

	return 0;
}
