#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

// 백준 2887 - 행성 터널
// union-find
// 플래티넘 5

// 1. x, y, z 정렬 후 양 옆 애들과만 edge 만들기
// => min(x 거리, y 거리, z 거리)이므로
// 2. 그 후 union-find

struct node
{
	int idx;
	int val;
	int idx2;
};
bool operator<(node n1, node n2)
{
	if (n1.val > n2.val) return true;
	return false;
}
bool cmp(node n1, node n2)
{
	if (n1.val < n2.val) return true;
	return false;
}
vector<node> xv;
vector<node> yv;
vector<node> zv;
priority_queue<node> pq;
int n;
int cost = 0;
int root[100001];

int find(int a)
{
	if (root[a] == a) return a;
	return root[a] = find(root[a]);
}
void Union(int a, int b, int w)
{
	int a_r = find(a);
	int b_r = find(b);
	if (a_r == b_r) return;
	cost += w;
	root[b_r] = a_r;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	int x, y, z;
	for (int i = 1; i <= n; i++)
	{
		root[i] = i;
		cin >> x >> y >> z;
		xv.push_back({ i, x });
		yv.push_back({ i, y });
		zv.push_back({ i, z });
	}
	sort(xv.begin(), xv.end(), cmp);
	sort(yv.begin(), yv.end(), cmp);
	sort(zv.begin(), zv.end(), cmp);

	// edge 만들기
	for (int i = 1; i < n; i++)
	{
		pq.push({ xv[i].idx, abs(xv[i].val - xv[i - 1].val), xv[i - 1].idx });
		pq.push({ yv[i].idx, abs(yv[i].val - yv[i - 1].val), yv[i - 1].idx });
		pq.push({ zv[i].idx, abs(zv[i].val - zv[i - 1].val), zv[i - 1].idx });
	}

	// union-find
	while (!pq.empty())
	{
		node tmp = pq.top();
		pq.pop();

		Union(tmp.idx, tmp.idx2, tmp.val);
	}

	cout << cost;

	return 0;
}