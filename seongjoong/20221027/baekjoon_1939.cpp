#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;

struct Edge {
	int num, limit;
};

int N, M;
vector<Edge> v[100001];
int A, B;
int visited[100001];
int ans;

bool bfs(int mid) {
	queue<int> q;
	q.push(A);
	visited[A] = 1;

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		// 도착지에 도달할 수 있으면 true
		if (now == B)
			return true;

		for (int i = 0; i < v[now].size(); i++) {
			Edge next = v[now][i];
			if (visited[next.num] == 1)
				continue;
			// 제한이 mid보다 작으면 mid 무게를 옮길 수 없으므로 패스
			if (next.limit < mid)
				continue;
			visited[next.num] = 1;
			q.push(next.num);
		}
	}
	
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;

	int left = 2134567890, right = 0;
	for (int i = 0; i < M; i++) {
		int from, to, limit;
		cin >> from >> to >> limit;
		v[from].push_back({ to,limit });
		v[to].push_back({ from,limit });
		left = min(left, limit);
		right = max(right, limit);
	}
	cin >> A >> B;

	// Binary search
	while (left <= right) {
		int mid = (left + right) / 2;
		memset(visited, 0, sizeof(visited));
		if (bfs(mid) == true) {
			ans = mid;
			// 더 큰 값이 가능한지 체크
			left = mid + 1;
		}
		else
			right = mid - 1;
	}
	
	cout << ans;

	return 0;
}
