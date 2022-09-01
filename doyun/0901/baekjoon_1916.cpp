#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 백준 1916 - 최소비용 구하기
// 골드 5
// dijkstra

struct vertex // 정점 
{
	int num;
	int dist = 100000000;
	int visit = 0; // visit : 1

};

struct edge // 간선
{
	int opposite;
	int weight = 0;
};

bool operator<(vertex e1, vertex e2)
{
	if (e1.dist > e2.dist) return true;
	return false;
}

vector<vertex> V;
vector<vector<edge>> E;
priority_queue <vertex> pq;

int main()
{
	int n, m;
	cin >> n >> m;

	V.resize(n + 1);
	for (int i = 1; i <= n; i++) V[i].num = i;

	int a, b, c;

	E.resize(n + 1);

	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		E[a].push_back({ b, c });
		//E[b].push_back({ a, c });
	}

	int start, end;
	cin >> start >> end;

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
			if (V[E[tmp.num][i].opposite].dist > E[tmp.num][i].weight + V[tmp.num].dist)
			{
				V[E[tmp.num][i].opposite].dist = E[tmp.num][i].weight + V[tmp.num].dist;
				pq.push(V[E[tmp.num][i].opposite]);
			}
		}

	}

	cout << V[end].dist;

	return 0;
}