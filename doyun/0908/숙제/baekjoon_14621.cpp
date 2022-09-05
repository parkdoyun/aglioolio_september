#include <iostream>
#include <queue>

using namespace std;

// 백준 14621 - 나만 안 되는 연애
// 골드 3
// MST

struct edge
{
	int start;
	int end;
	int weight;
};

bool operator<(edge e1, edge e2)
{
	if (e1.weight > e2.weight) return true;
	return false;
}

int parent[1001];
int teamNum[1001];
char school[1001];
priority_queue<edge> pq;

int Find(int a)
{
	if (parent[a] == a) return a;
	return Find(parent[a]);
}

void Union(int a, int b)
{
	if (Find(a) == Find(b)) return;
	teamNum[Find(b)] += teamNum[Find(a)];
	teamNum[Find(a)] = 0;
	parent[Find(a)] = Find(b);
}

int kruskal()
{
	int sum = 0;
	while (!pq.empty())
	{
		edge tmp = pq.top();
		pq.pop();

		// 남학교끼리, 여학교끼리라면 pass
		if (school[tmp.start] == school[tmp.end]) continue;
		if (Find(tmp.start) == Find(tmp.end)) continue;
		Union(tmp.start, tmp.end);
		sum += tmp.weight;
	}
	return sum;
}
int main()
{
	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
	{
		parent[i] = i;
		teamNum[i] = 1;
	}

	for (int i = 1; i <= n; i++)
	{
		cin >> school[i];
	}

	int u, v, d;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> d;
		pq.push({ u, v, d });
	}

	int res = kruskal();

	int chk = 0;
	for (int i = 1; i <= n; i++)
	{
		if (teamNum[i] == 1)
		{
			chk = 1;
			break;
		}
	}

	if (chk == 1) // 모두 연결되지 않았다면
	{
		cout << -1;
	}
	else
	{
		cout << res;
	}

	return 0;
}