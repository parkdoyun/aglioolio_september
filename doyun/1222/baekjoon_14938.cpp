#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 백준 14938 - 서강그라운드
// dijkstra
// 골드 4

// dist : m 이하로 dijkstra 진행
// 만약 dijkstra로 그래프에 연결되면 해당 정점의 item 더한다 (now_item)
// 모든 정점에서 dijkstra 다 해보고 구한 now_item 중 최댓값 출력

#define INF 1000000

struct vertex
{
	int idx;
	int dist = INF;
	int item; // 아이템
	int visit = -1;
};
bool operator<(vertex v1, vertex v2)
{
	if (v1.dist > v2.dist) return true;
	return false;
}
struct edge
{
	int oppo;
	int weight;
};
int n, m, r;
int now_item; // 현재 먹은 item
vector<vertex> V;
vector<vector<edge>> E;
priority_queue<vertex> pq;

void dijkstra(int start)
{
	V[start].dist = 0;
	now_item = 0;
	pq.push(V[start]);
	
	while (!pq.empty())
	{
		vertex tmp = pq.top();
		pq.pop();

		if (V[tmp.idx].visit == 1) continue;
		V[tmp.idx].visit = 1;
		if (V[tmp.idx].dist > m) continue;
		now_item += V[tmp.idx].item;

		for (int i = 0; i < E[tmp.idx].size(); i++)
		{
			if (V[E[tmp.idx][i].oppo].dist > V[tmp.idx].dist + E[tmp.idx][i].weight)
			{
				V[E[tmp.idx][i].oppo].dist = V[tmp.idx].dist + E[tmp.idx][i].weight;
				pq.push(V[E[tmp.idx][i].oppo]);
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m >> r;
	V.resize(n + 1);
	E.resize(n + 1);
	for (int i = 1; i <= n; i++)
	{
		V[i].idx = i;
		cin >> V[i].item;
	}
	int a, b, w;
	for (int i = 0; i < r; i++)
	{
		cin >> a >> b >> w;
		E[a].push_back({ b, w });
		E[b].push_back({ a, w });
	}

	// 각 지점마다 dijkstra -> 최대 찾자
	int max1 = 0;
	for (int i = 1; i <= n; i++)
	{
		dijkstra(i);
		if (now_item > max1) max1 = now_item;
		// 초기화
		for (int i = 1; i <= n; i++)
		{
			V[i].dist = INF;
			V[i].visit = -1;
		}
	}

	cout << max1;

	return 0;
}