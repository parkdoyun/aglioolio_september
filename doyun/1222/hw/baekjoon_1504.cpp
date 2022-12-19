#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 백준 1504 - 특정한 최단 경로
// dijkstra
// 골드 4

// i) 1 -> v1 -> v2 -> 2
// 1 -> v1, v1 -> v2, v2 -> 2 각각 구해서 더한다
// ii) 1 -> v2 -> v1 -> 2 
// 1 -> v2, v1 -> 2 구해서 더한 후 작은 값 출력

struct vertex
{
	int idx;
	int dist = 200000001;
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
vector<vertex> V;
vector<vector<edge>> E;
priority_queue<vertex> pq;

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
			if (V[E[tmp.idx][i].oppo].dist > V[tmp.idx].dist + E[tmp.idx][i].weight)
			{
				V[E[tmp.idx][i].oppo].dist = V[tmp.idx].dist + E[tmp.idx][i].weight;
				pq.push(V[E[tmp.idx][i].oppo]);
			}
		}
	}
}
int n, e;
void clear()
{
	for (int i = 1; i <= n; i++)
	{
		V[i].visit = -1;
		V[i].dist = 200000001;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> e;

	V.resize(n + 1);
	E.resize(n + 1);

	for (int i = 1; i <= n; i++)
	{
		V[i].idx = i;
	}

	int a, b, c;
	for (int i = 0; i < e; i++)
	{
		cin >> a >> b >> c;
		E[a].push_back({ b, c });
		E[b].push_back({ a, c });
	}

	int v1, v2;
	cin >> v1 >> v2;

	// v1 -> v2 구하기
	int v1Tov2, oneTov1, oneTov2, v2ToN, v1ToN;

	dijkstra(v1);
	if (V[v2].dist != 200000001)
	{
		v1Tov2 = V[v2].dist;
	}
	else
	{
		cout << -1;
		return 0;
	}
	// v1-> n
	if (V[n].dist != 200000001) v1ToN = V[n].dist;
	else v1ToN = -1;
	
	clear();
	dijkstra(1);
	// 1 -> v2
	if (V[v2].dist != 200000001) oneTov2 = V[v2].dist;
	else oneTov2 = -1;
	// 1 -> v1
	if (V[v1].dist != 200000001) oneTov1 = V[v1].dist;
	else oneTov1 = -1;

	clear();
	dijkstra(v2);
	// v2 -> n
	if (V[n].dist != 200000001) v2ToN = V[n].dist;
	else v2ToN = -1;

	// min 비교
	int res1, res2;
	if (v1Tov2 == -1 || oneTov1 == -1 || v2ToN == -1) res1 = -1;
	else res1 = oneTov1 + v1Tov2 + v2ToN;
	if (v1Tov2 == -1 || oneTov2 == -1 || v1ToN == -1) res2 = -1;
	else res2 = oneTov2 + v1Tov2 + v1ToN;

	if (res1 != -1 && res2 != -1)
	{
		if (res1 < res2) cout << res1;
		else cout << res2;
	}
	else if (res1 == -1 && res2 != -1) cout << res2;
	else if (res2 == -1 && res1 != -1) cout << res1;
	else cout << -1;


	return 0;
}