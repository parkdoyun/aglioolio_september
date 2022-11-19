#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 백준 10282 - 해킹
// dijkstra
// 골드 4

// 가장 나중 컴퓨터 시간 출력
// dijkstra 기준 : s 시간 제일 낮은 곳부터

int n, d, c;

struct vertex
{
	int idx;
	int dist = 100000000000;
	int visit = 0; // 1 : visit
};
struct edge
{
	int oppo;
	int s;
};

vector<vector<edge>> E;
vector<vertex> V;


bool operator<(vertex v1, vertex v2)
{
	if (v1.dist > v2.dist) return true;
	return false;
}
priority_queue<vertex> pq;

int max_time = 0; // 마지막 시간
int cnt = 0;

void dijkstra(int start)
{
	while (!pq.empty()) pq.pop();

	V[start].dist = 0;

	pq.push({ V[start] });

	while (!pq.empty())
	{
		vertex tmp = pq.top();
		pq.pop();

		if (V[tmp.idx].visit == 1) continue;
		V[tmp.idx].visit = 1;
		if (tmp.dist > max_time) max_time = tmp.dist;
		cnt++;

		for (int i = 0; i < E[tmp.idx].size(); i++)
		{
			if (V[E[tmp.idx][i].oppo].visit == 0 &&
				V[E[tmp.idx][i].oppo].dist > tmp.dist + E[tmp.idx][i].s)
			{
				V[E[tmp.idx][i].oppo].dist = tmp.dist + E[tmp.idx][i].s;
				pq.push({ E[tmp.idx][i].oppo , tmp.dist + E[tmp.idx][i].s });
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> n >> d >> c; // c : 시작
		int a, b, s;
		E.resize(n + 1);
		V.resize(n + 1);
		max_time = 0;
		cnt = 0;

		for (int i = 1; i <= n; i++)
		{
			V[i].idx = i;
		}

		for (int i = 0; i < d; i++)
		{
			cin >> a >> b >> s;
			E[b].push_back({ a, s });
		}

		dijkstra(c);

		cout << cnt << ' ' << max_time << '\n';

		V.clear();
		for (int i = 0; i < n; i++)
		{
			E[i].clear();
		}
		E.clear();
	}


	return 0;
}