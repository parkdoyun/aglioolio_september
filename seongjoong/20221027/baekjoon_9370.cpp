#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
	int num, cost;
};

struct EdgeFlag {
	int num, cost, flag; // A~B 도로를 지나서 왔는가?
};

bool operator<(EdgeFlag a, EdgeFlag b) {
	if (a.cost < b.cost) return false;
	if (a.cost > b.cost) return true;
	return false;
}

int T;
int N, M, K;
int S, A, B;
vector<Edge> v[2001];
vector<int> ans;

void init() {
	for (int i = 0; i < 2001; i++)
		v[i].clear();
	ans.clear();
}

// 목적지 후보들까지의 최단 경로를 구한 후
// -> A~B 도로를 지나왔는지 체크
void dijkstra(int end) {
	priority_queue<EdgeFlag> pq;
	pq.push({ S,0,0 });

	int dist[2001] = { 0 };
	for (int i = 1; i <= N; i++)
		dist[i] = 2134567890;
	dist[S] = 0;

	int flag[2001] = { 0 };

	while (!pq.empty()) {
		EdgeFlag now = pq.top();
		pq.pop();

		if (dist[now.num] < now.cost)
			continue;

		for (int i = 0; i < (int)v[now.num].size(); i++) {
			Edge next = v[now.num][i];
			int nextCost = now.cost + next.cost;
			int nextFlag = now.flag;

			// A~B 도로를 지나는지 체크
			if ((now.num == A && next.num == B) || (now.num == B && next.num == A))
				nextFlag = 1;
			// *** 최단거리의 경로가 여러 개 있을 수 있으므로 등호 X ***
			if (dist[next.num] < nextCost)
				continue;
			// A~B를 지나는 같은 거리의 경로를 이미 찾았으면 패스
			if (dist[next.num] == nextCost && flag[next.num] == 1)
				continue;

			dist[next.num] = nextCost;
			flag[next.num] = nextFlag;
			pq.push({ next.num,nextCost,nextFlag });
		}
	}
	
	if (flag[end] == 1 && dist[end] != 2134567890)
		ans.push_back(end);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();

		cin >> N >> M >> K;
		cin >> S >> A >> B;
		for (int i = 0; i < M; i++) {
			int from, to, cost;
			cin >> from >> to >> cost;
			v[from].push_back({ to,cost });
			v[to].push_back({ from,cost });
		}

		for (int i = 0; i < K; i++) {
			int n;
			cin >> n;
			dijkstra(n);
		}

		sort(ans.begin(), ans.end());
		for (int i = 0; i < (int)ans.size(); i++)
			cout << ans[i] << " ";
		cout << '\n';
	}

	return 0;
}
