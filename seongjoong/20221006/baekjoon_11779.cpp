#include <iostream>
#include <queue>
using namespace std;

struct Edge {
	int num, cost;
};

bool operator<(Edge a, Edge b) {
	if (a.cost < b.cost) return false;
	if (a.cost > b.cost) return true;
	return false;
}

struct Path {
	int cost;
	vector<int> path;
};

int N, M;
int A, B;
vector<Edge> v[1001];

void dijkstra(int node) {
	// pq 세팅
	priority_queue<Edge> pq;
	pq.push({ node,0 });

	// dist 세팅
	Path dist[1001] = { 0 };
	for (int i = 1; i <= N; i++)
		dist[i].cost = 2134567890;
	dist[node].cost = 0; // 출발점 -> 출발점 비용 = 0
	dist[node].path.push_back(node);

	// dijkstra
	while (!pq.empty()) {
		Edge now = pq.top();
		pq.pop();

		if (dist[now.num].cost < now.cost)
			continue;

		for (int i = 0; i < v[now.num].size(); i++) {
			Edge next = v[now.num][i];
			int nextCost = dist[now.num].cost + next.cost;

			// 기록되어 있는 최소값보다 크면 패스
			if (dist[next.num].cost <= nextCost)
				continue;

			dist[next.num].cost = nextCost;
			// 기록되어 있는 next까지의 경로 초기화
			dist[next.num].path.clear();
			// 현재까지 경로 복사
			for (int i = 0; i < dist[now.num].path.size(); i++)
				dist[next.num].path.push_back(dist[now.num].path[i]);
			// next 삽입
			dist[next.num].path.push_back(next.num);

			pq.push({ next.num,nextCost });
		}
	}

	cout << dist[B].cost << '\n';
	cout << dist[B].path.size() << '\n';
	for (int i = 0; i < dist[B].path.size(); i++)
		cout << dist[B].path[i] << " ";
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
	cin >> A >> B;

	dijkstra(A);

	return 0;
}
