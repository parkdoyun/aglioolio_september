#include <iostream>
#include <queue>

using namespace std;

// πÈ¡ÿ 1197 - √÷º“ Ω∫∆–¥◊ ∆Æ∏Æ
// union-find, MST
// ∞ÒµÂ 4

int root[10001];

int find(int a)
{
	if (root[a] == a) return a;
	return find(root[a]); // find æ» ª©∏‘∞‘ ¡∂Ω…
}

int total_w = 0;
void Union(int a, int b, int w)
{
	int a_r = find(a);
	int b_r = find(b);

	if (a_r == b_r) return;
	total_w += w;
	root[b_r] = a_r;
}
int v, e;
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
priority_queue<node> pq;


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> v >> e;
	for (int i = 1; i <= v; i++)
	{
		root[i] = i;
	}

	int a, b, c;
	for (int i = 0; i < e; i++)
	{
		cin >> a >> b >> c;
		pq.push({ a, b, c });
	}

	while (!pq.empty())
	{
		node tmp = pq.top();
		pq.pop();

		Union(tmp.a, tmp.b, tmp.weight);
	}

	cout << total_w;

	return 0;
}