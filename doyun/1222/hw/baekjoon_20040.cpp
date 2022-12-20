#include <iostream>

using namespace std;

// 백준 20040 - 사이클 게임
// union-find
// 골드 4

// union-find
// 새로 연결하려는 지점이 이미 같은 구역이라면 cycle

int n, m;
int root[500001];

int find(int a)
{
	if (root[a] == a) return a;
	return find(root[a]);
}

bool Union(int a, int b)
{
	int a_r = find(a);
	int b_r = find(b);
	if (a_r == b_r) return false;

	root[b_r] = a_r;
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; i++) root[i] = i;

	int a, b;
	int flag = 0;
	for (int i = 1; i <= m; i++)
	{
		cin >> a >> b;
		if (Union(a, b) == false)
		{
			flag = 1;
			cout << i;
			break;
		}
	}
	if (flag == 0) cout << 0;

	return 0;
}