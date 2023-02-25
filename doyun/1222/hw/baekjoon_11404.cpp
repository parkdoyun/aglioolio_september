#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 백준 11404 - 플로이드
// dijkstra
// 골드 4

// 원래 플로이드-워셜 문제인 듯
// 다익스트라로 품

struct vertex
{
	int idx;
	int dist = 100000000;
	int visit = -1;
};
struct edge
{
	int oppo;
	int weight;
};
bool operator<(vertex v1, vertex v2)
{
	if (v1.dist > v2.dist) return true;
	return false;
}

vector<vertex> V;
vector<vector<edge>> E;
priority_queue<vertex> pq;
int n, m;

void dijkstra(int start)
{
	while (!pq.empty()) pq.pop();

	V[start].dist = 0;
	pq.push(V[start]);
	
	while (!pq.empty())
	{
		vertex tmp = pq.top();
		pq.pop();

		if (V[tmp.idx].visit == 1) continue;
		V[tmp.idx].visit = 1;

		for (int i = 0; i < E[tmp.idx].size(); i++)
		{
			if (V[E[tmp.idx][i].oppo].dist > E[tmp.idx][i].weight + V[tmp.idx].dist)
			{
				V[E[tmp.idx][i].oppo].dist = E[tmp.idx][i].weight + V[tmp.idx].dist;
				pq.push(V[E[tmp.idx][i].oppo]);
			}
		}
	}
}
void print()
{
	for (int i = 1; i <= n; i++)
	{
		if (V[i].dist == 100000000) cout << 0 << ' ';
		else cout << V[i].dist << ' ';
		V[i].visit = -1;
		V[i].dist = 100000000;
	}
	cout << '\n';
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	V.resize(n + 1);
	E.resize(n + 1);

	for (int i = 1; i <= n; i++) V[i].idx = i;

	int a, b, c;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		E[a].push_back({ b, c });
	}

	for (int i = 1; i <= n; i++)
	{
		dijkstra(i);
		print();
	}

	return 0;
}