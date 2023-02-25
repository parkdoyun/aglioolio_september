#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 백준 1719 - 택배
// dijkstra
// 골드 3

// 모든 다익스트라 경로 구해야 함
// 모든 정점마다 다익스트라 한 후
// 거꾸로 거슬러 올라가면서 경로표 정리

int n, m;
int path[201][201];
int pre_vertex[201]; // 이전 (타고타고 올라가기)

struct vertex
{
	int idx;
	int dist = 10000000000;
	int visit = 0; // 1 : visited
};

struct edge
{
	int oppo;
	int weight;
};

vector<vertex> V;
vector<vector<edge>> E;

bool operator<(vertex v1, vertex v2)
{
	if (v1.dist > v2.dist) return true;
	return false;
}

priority_queue<vertex> pq;
void dijkstra(int start)
{
	while (!pq.empty()) pq.pop();

	V[start].dist = 0;
	pq.push(V[start]);
	pre_vertex[start] = start;
	
	while (!pq.empty())
	{
		vertex tmp = pq.top();
		pq.pop();
		if (V[tmp.idx].visit == 1) continue;
		V[tmp.idx].visit = 1;

		for (int i = 0; i < E[tmp.idx].size(); i++)
		{
			if (E[tmp.idx][i].weight + V[tmp.idx].dist < V[E[tmp.idx][i].oppo].dist)
			{
				V[E[tmp.idx][i].oppo].dist = E[tmp.idx][i].weight + V[tmp.idx].dist;
				pq.push(V[E[tmp.idx][i].oppo]);
				pre_vertex[E[tmp.idx][i].oppo] = tmp.idx;
			}
		}
	}

}
void vertexClear()
{
	for (int i = 1; i <= n; i++)
	{
		V[i].dist = 10000000000;
		V[i].visit = 0;
		pre_vertex[i] = -1;
	}
}

int main()
{
	cin >> n >> m;

	V.resize(n + 1);
	E.resize(n + 1);
	for (int i = 1; i <= n; i++)
	{
		V[i].idx = i;
	}

	int a, b, w;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> w;
		E[a].push_back({ b, w });
		E[b].push_back({ a, w });
	}

	for (int i = 1; i <= n; i++)
	{
		vertexClear();
		dijkstra(i);
		// 경로표 작성 (거꾸로)
		// pre_vertex 타고타고 올라가서 최초 적기
		for (int j = 1; j <= n; j++)
		{
			if (i == j)
			{
				path[i][j] = 0;
				continue;
			}
			int tmp_v = j;
			while (true)
			{
				if (pre_vertex[tmp_v] == i) break;
				tmp_v = pre_vertex[tmp_v];
			}
			path[i][j] = tmp_v;
		}
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (path[i][j] == 0) cout << "- ";
			else cout << path[i][j] << ' ';
		}
		cout << '\n';
	}

	return 0;
}