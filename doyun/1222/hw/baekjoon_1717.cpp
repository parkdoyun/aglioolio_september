#include <iostream>

using namespace std;

// 백준 1717 - 집합의 표현
// union-find
// 골드 4

int n, m;
int root[1000002];

int find(int a)
{
	if (root[a] == a) return a;
	return root[a] = find(root[a]);
}
void Union(int a, int b)
{
	int a_r = find(a);
	int b_r = find(b);
	if (a_r == b_r) return;
	root[b_r] = a_r;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;

	for (int i = 0; i <= n; i++)
	{
		root[i] = i;
	}

	int order, a, b;
	for (int i = 0; i < m; i++)
	{
		cin >> order >> a >> b;
		if (order == 0)
		{
			Union(a, b);
		}
		else
		{
			if (find(a) != find(b)) cout << "NO\n";
			else cout << "YES\n";
		}
	}

	return 0;
}