#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
	int p;
	int f;
	int s;
	int v;
	int cost;
};

int n;
vector<Node> ingredient;
int mp, mf, ms, mv;

int minCost = 10000;

vector<int> path;
vector<int> minPath;
void dfs(int level, int cost, int p, int f, int s, int v) {

	if (minCost < cost) return;

	if (mp <= p && mf <= f && ms <= s && mv <= v) {
		if (minCost > cost) {
			minCost = cost;
			minPath = path;
		}
		return;
	}

	if (level >= n) {
		return;
	}

	Node now = ingredient[level];
	path.push_back(level);
	dfs(level + 1, cost + now.cost, p + now.p, f + now.f, s + now.s, v + now.v);
	path.pop_back();
	dfs(level + 1, cost, p, f, s, v);
}

int main()
{
	cin >> n;

	cin >> mp >> mf >> ms >> mv;

	for (int i = 0; i < n; i++) {
		int p, f, s, v, cost;
		cin >> p >> f >> s >> v >> cost;
		ingredient.push_back({ p, f, s, v, cost });
	}

	dfs(0, 0, 0, 0, 0, 0);

	if (minCost != 10000) {
		cout << minCost << "\n";
		sort(minPath.begin(), minPath.end());
		for (int i = 0; i < minPath.size(); i++) {
			cout << minPath[i] + 1 << " ";
		}
	}
	else {
		cout << -1;
	}

	return 0;
}