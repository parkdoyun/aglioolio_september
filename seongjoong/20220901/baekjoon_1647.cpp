#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
	int a, b, cost;
};

bool cmp(Edge a, Edge b) {
	// 비용 작은 게 우선
	if (a.cost < b.cost) return true;
	if (a.cost > b.cost) return false;
	return false;
}

int N, M;
vector<Edge> v;
int parent[100001];

int Find(int node) {
	if (node == parent[node])
		return node;
	return parent[node] = Find(parent[node]);
}

void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);

	if (pa == pb) return;

	parent[pb] = pa;
}

int kruskal() {
	// 비용이 작은 것부터 정렬
	sort(v.begin(), v.end(), cmp);

	int sum = 0; // 모든 길 비용 총합
	int maxval = -2134567890; // 최대비용
	for (int i = 0; i < v.size(); i++) {
		Edge now = v[i];

		// 두 마을이 이미 연결되어 있는가
		if (Find(v[i].a) == Find(v[i].b))
			continue;
		// 아니라면 길을 놔준다.
		sum += now.cost;
		// 지금 놔준 길이 최대값보다 크면 갱신
		if (now.cost > maxval)
			maxval = now.cost;
		// 길을 놔줬으니 대표 같게 만들기
		Union(v[i].a, v[i].b);
	}
	// 모두 연결시킨 후 가장 비싼 길 삭제
	return sum - maxval;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// 1. 임의의 두 집 사이에 경로가 항상 존재해야 한다.
	// --> Union Find / MST

	// 2. 마을을 두 개로 분리
	// --> MST를 만들고 그 중에서 가장 비용이 큰 간선 제거

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b, cost;
		cin >> a >> b >> cost;
		v.push_back({ a,b,cost });
	}

	// parent 초기화
	for (int i = 1; i <= N; i++)
		parent[i] = i;

	int ans = kruskal();
	cout << ans;

	return 0;
}