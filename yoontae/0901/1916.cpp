#include<iostream>
#include<queue>
#include<vector>

using namespace std;

struct Edge {
	int to;
	int cost;
};

bool operator < (Edge A, Edge B) {
	if (A.cost < B.cost)
		return false;
	if (A.cost > B.cost)
		return true;
	return false;
}

int N, M;
vector<Edge>v[1001];
int startCity, endCity;
int dist[1001];


void input() {

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		v[from].push_back({ to,cost });
	}

	cin >> startCity >> endCity;
}

void dijkstra(int city) {

	priority_queue<Edge>pq;

	for (int i = 1; i <= N; i++) {
		dist[i] = 2134567890;
	}

	dist[city] = 0;

	pq.push({ city,0 });

	while (!pq.empty()) {

		Edge now = pq.top();
		pq.pop();

		if (dist[now.to] < now.cost)
			continue;

		for (int i = 0; i < v[now.to].size(); i++) {
			int next = v[now.to][i].to;
			
			int nextcost = dist[now.to] + v[now.to][i].cost;

			if (dist[next] <= nextcost)
				continue;

			dist[next] = nextcost;
			pq.push({ next,nextcost });
		}
	}
}

int solution() {

	dijkstra(startCity);

	return dist[endCity];
}

int main()
{
	input();

	cout << solution() << "\n";

	return 0;
}