#include <iostream>
#include <queue>

using namespace std;

// 백준 16398 - 행성 연결
// union-find
// 골드 4

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

int n;
int root[1001];
long long int total_cost = 0;

int find(int a)
{
	if (root[a] == a) return a;
	return root[a] = find(root[a]);
}

void Union(int a, int b, long long int w)
{
	int a_r = find(a);
	int b_r = find(b);
	if (a_r == b_r) return;
	total_cost = (long long int)(total_cost + w);
	root[b_r] = a_r;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) root[i] = i;

	long long int a;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> a;
			if (j >= i) continue;
			pq.push({ i, j, a });
		}
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