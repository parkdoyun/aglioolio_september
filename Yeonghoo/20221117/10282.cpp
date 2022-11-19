//b -> a
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
	int to;
	int cost;
};

bool operator< (Node a, Node b) {
	if (a.cost < b.cost)
		return false;
	if (a.cost > b.cost)
		return true;
	return false;
}

int n, d, c;
vector<Node> graph[10001];

void init() {
	for (int i = 0; i < 10001; i++)
		graph[i].clear();
}

void input() {
	cin >> n >> d >> c;
	for (int i = 0; i < d; i++) {
		int a, b, s;
		cin >> a >> b >> s;
		graph[b].push_back({ a,s });
	}
}

void dijkstra(int start) {
	priority_queue<Node> pq;
	
	int dist[10001];
	for (int i = 0; i <= n; i++)
		dist[i] = 2123456789;
	
	pq.push({ start, 0 });
	dist[start] = 0;

	while (!pq.empty()) {
		Node now = pq.top();
		pq.pop();
		
		if (dist[now.to] < now.cost)
			continue;

		for (int i = 0; i < graph[now.to].size(); i++) {
			Node next = graph[now.to].at(i);

			int nextcost = dist[now.to] + next.cost;

			if (dist[next.to] <= nextcost)
				continue;
			
			dist[next.to] = nextcost;
			pq.push({ next.to, nextcost });
		}
	}
	int cnt = 0;
	int time = -2123456789;

	for (int i = 0; i <= n; i++) {
		if (dist[i] != 2123456789) {
			cnt++;
			time = (dist[i] > time) ? dist[i] : time;
		}
	}

	cout << cnt << " " << time << '\n';
}
int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int T;
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		init();
		input();
		dijkstra(c);
	}
}
