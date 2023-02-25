#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// 백준 6497 - 전력난
// union-find
// 골드 4

// union로 최소만 연결하면
// 나머지는 연결할 필요 없다 => 전부 절약하는 비용

// union-find 시간 단축 코드 익혀두기

int n, m;
int root[200001];

struct node
{
	int a;
	int b;
	int weight;
};
bool operator<(node n1, node n2)
{
	if (n1.weight > n2.weight) return true;
	return false;
}
bool cmp(node n1, node n2)
{
	if (n1.weight < n2.weight) return true;
	return false;
}
vector<node> vec;
int cost;

int find(int a)
{
	if (root[a] == a) return a;
	return root[a] = find(root[a]); // 이렇게 하면 시간 단축됨
}

void Union(int a, int b, int w)
{
	int a_r = find(a);
	int b_r = find(b);
	if (a_r == b_r)
	{
		cost += w;
		return;
	}
	root[b_r] = a_r;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int x, y, z;
	vec.resize(200001);
	while (true)
	{
		cin >> n >> m;
		if (n == 0 && m == 0) break;

		for (int i = 0; i < n; i++) root[i] = i; // **실수 안 하도록 주의**

		for (int i = 0; i < m; i++)
		{
			cin >> x >> y >> z;
			vec[i].a = x;
			vec[i].b = y;
			vec[i].weight = z;
		}

		sort(vec.begin(), vec.begin() + m, cmp);
		cost = 0;

		for (int i = 0; i < m; i++)
		{
			Union(vec[i].a, vec[i].b, vec[i].weight);
		}
		cout << cost << '\n';
	}

	return 0;
}