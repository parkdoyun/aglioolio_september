#include <iostream>

using namespace std;

// 백준 1976 - 여행 가자
// union-find
// 골드 4

// union-find로 모든 도시 연결함
// root 같다면 이동 가능

int n, m;
int root[201];

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
	for (int i = 1; i <= n; i++) root[i] = i;

	int a, b;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> a;
			if (a == 1) Union(i, j);
		}
	}

	cin >> a;
	int flag = 0;
	for (int i = 1; i < m; i++)
	{
		cin >> b;
		if (find(a) != find(b)) flag = 1;
		a = b;
	}

	if (flag == 1) cout << "NO";
	else cout << "YES";


	return 0;
}