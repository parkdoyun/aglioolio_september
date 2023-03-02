#include <iostream>
#include <queue>

using namespace std;

// 백준 14950 - 정복자
// union-find
// 골드 3

struct edge
{
	int a;
	int b;
	long long int w;
};
bool operator<(edge e1, edge e2)
{
	if (e1.w > e2.w) return true;
	return false;
}
priority_queue<edge> pq;

int n, m, t;
int root[10001];
long long int total_cost = 0;

int find(int a)
{
	if (root[a] == a) return a;
	return root[a] = find(root[a]);
}

int idx = 0;
void Union(int a, int b, long long int w)
{
	int a_r = find(a);
	int b_r = find(b);
	if (a_r == b_r) return;
	total_cost = (long long int)(total_cost + w);
	total_cost = (long long int)(total_cost + (long long int)(idx * t));
	idx++;
	root[b_r] = a_r;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m >> t;
	for (int i = 0; i < n; i++) root[i] = i;

	int x, y;
	long long int a;
	for (int i = 0; i < m; i++)
	{
		cin >> x >> y >> a;
		pq.push({ x, y, a });
	}

	while (!pq.empty())
	{
		edge tmp = pq.top();
		pq.pop();

		Union(tmp.a, tmp.b, tmp.w);
	}

	cout << total_cost;

	return 0;
}