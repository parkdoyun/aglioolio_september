#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 백준 1753 - 최단경로
// 골드 4
// dijkstra
// 각 정점마다 간선들 weight 작은 순으로 sort

struct vertex
{
	int num;
	int dist = 10000000;
	int visit = 0;
};

struct edge
{
	int oppo; // 반대편
	int weight;
};

bool operator<(vertex v1, vertex v2)
{
	if (v1.dist > v2.dist) return true;
	return false;
}

bool cmp(edge e1, edge e2)
{
	if (e1.weight < e2.weight) return true;
	return false;
}

vector<vector<edge>> E;
vector<vertex> V;
priority_queue<vertex> pq;

int main()
{
	int v, e;
	cin >> v >> e;

	V.resize(v + 1);
	E.resize(v + 1);

	for (int i = 1; i <= v; i++) V[i].num = i;

	int start;
	cin >> start;

	int u1, v1, w1;
	for (int i = 0; i < e; i++)
	{
		cin >> u1 >> v1 >> w1;
		E[u1].push_back({ v1, w1 });
	}

	// 각 정점마다 간선들 weight 작은 순으로 sort
	for (int i = 1; i <= v; i++)
	{
		sort(E[i].begin(), E[i].end(), cmp);
	}

	// dijkstra 수행
	V[start].dist = 0;
	pq.push(V[start]);

	while (!pq.empty())
	{
		vertex tmp = pq.top();
		pq.pop();

		if (V[tmp.num].visit == 1) continue;
		V[tmp.num].visit = 1;

		for (int i = 0; i < E[tmp.num].size(); i++)
		{
			if (V[E[tmp.num][i].oppo].dist > V[tmp.num].dist + E[tmp.num][i].weight)
			{
				V[E[tmp.num][i].oppo].dist = V[tmp.num].dist + E[tmp.num][i].weight;
				pq.push(V[E[tmp.num][i].oppo]);
			}
		}

	}

	for (int i = 1; i <= v; i++)
	{
		if (V[i].dist == 10000000) cout << "INF\n";
		else cout << V[i].dist << '\n';
	}

	return 0;

}

