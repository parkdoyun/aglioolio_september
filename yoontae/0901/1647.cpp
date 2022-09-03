#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

struct Edge {
	int a;
	int b;
	int cost;
};

int N, M;
vector<Edge>Road;
int parent[100001];
int cnt;

bool cmp(Edge A, Edge B) {
	if (A.cost < B.cost)
		return true;
	if (A.cost > B.cost)
		return false;
	return false;
}

void input() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b, cost;
		cin >> a >> b >> cost;
		Road.push_back({ a,b,cost });
	}
}

int Find(int node) {
	if (node == parent[node])
		return node;
	return parent[node] = Find(parent[node]);
}

void Union(int a, int b) {
	int pA = Find(a);
	int pB = Find(b);

	if (pA == pB)
		return;

	parent[pB] = pA;
	cnt--;
}

int solution() {

	for (int i = 1; i <= N; i++)
		parent[i] = i;
	
	cnt = N;

	sort(Road.begin(), Road.end(), cmp);

	int sum = 0;

	for (int i = 0; i < Road.size(); i++) {
		Edge now = Road[i];

		if (Find(now.a) == Find(now.b))
			continue;

		Union(now.a, now.b);
		sum += now.cost;

		if (cnt == 2)
			break;
	}

	return sum;
}

int main() {
	input();
	cout << solution() << "\n";

	return 0;
}