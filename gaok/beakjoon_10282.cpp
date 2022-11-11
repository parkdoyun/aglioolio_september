#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
	int to;
	int cost;
};

bool operator < (Node a, Node b) {
	if (a.cost > b.cost) return true;
	if (a.cost < b.cost) return false;
	return false;
}

int n, d, c;
vector<Node> computers[10001];

void dijkstra() {

	priority_queue<Node> pq;
	int visited[10001]={0};
	int dist[10001]={0};
	
	int cnt=0;
	long long time=0;

	for (int i = 0; i < 10001; i++) {
		dist[i] = 2134567890;
	}

	dist[c] = 0;
	pq.push({ c, 0 });

	while (!pq.empty()) {
		int nowCost = pq.top().cost;
		int now = pq.top().to;
		
		pq.pop();

		if (visited[now] != 0) continue;
		visited[now] = 1;

		for (int i = 0; i < computers[now].size(); i++) {
			int nextCost = computers[now][i].cost;
			int next = computers[now][i].to;

			if (dist[next] <= nextCost + dist[now]) continue;
			dist[next] = nextCost + dist[now];

			pq.push({ next, dist[next]});
		}
	}

	for (int i = 1; i < 10001; i++) {
		if (dist[i] == 2134567890) continue;
		if (time < dist[i]) time = dist[i];
		cnt++;
	}
	cout << cnt << " " << time << "\n";
}

void init() {
	
	for (int i = 0; i < 10001; i++) {
		computers[i].clear();
	}
}

int main() {

	int testcase;
	cin >> testcase;

	for (int t = 0; t < testcase; t++) {
	
		cin >> n >> d >> c;

		for (int j = 0; j < d; j++) {
			int a, b, s;
			cin >> a >> b >> s;
			computers[b].push_back({ a, s });
		}

		dijkstra();

		init();
	}

	return 0;
}

