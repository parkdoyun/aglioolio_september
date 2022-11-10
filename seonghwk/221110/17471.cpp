#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N;
int population[11];
vector<int> v[11];
int region[11];
int min_diff;

bool bfs(vector<int> a, vector<int> b) {
	int visited[11] = {};

	queue<int> q;
	q.push(a[0]);
	q.push(b[0]);
	visited[a[0]] = 1;
	visited[b[0]] = 1;
	while (!q.empty()) {
		int now = q.front();
		q.pop();

		for (int i = 0; i < v[now].size(); i++) {
			int next = v[now][i];
			if (region[now] != region[next])
				continue;
			if (visited[next] != 0)
				continue;
			visited[next] = 1;
			q.push(next);
		}
	}
	for (int i = 1; i <= N; i++) {
		if (visited[i] == 0)
			return false;
	}
	return true;

}

int getDiff() {
	vector<int> a, b;
	int cnt_a = 0, cnt_b = 0;
	for (int i = 1; i <= N; i++) {
		if (region[i] == 1) {
			a.push_back(i);
			cnt_a += population[i];
		}
		else {
			b.push_back(i);
			cnt_b += population[i];
		}
	}
	if (a.size() == 0 || b.size() == 0)
		return 2147483647;
	if (bfs(a, b) == true) {
		return abs(cnt_a - cnt_b);
	}
	else
		return 2147483647;

}

void dfs(int level) {
	// base case
	if (level == N + 1) {
		min_diff = min(min_diff, getDiff());
		return;
	}
	// recursive case
	region[level] = 1;
	dfs(level + 1);
	region[level] = 0;
	dfs(level + 1);
}

void solution() {
	min_diff = 2147483647;
	dfs(1);
	if (min_diff == 2147483647) {
		cout << -1;
	}
	else {
		cout << min_diff;
	}
}

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> population[i];
	}
	int adj_cnt;
	for (int i = 1; i <= N; i++) {
		cin >> adj_cnt;
		int adj_id;
		for (int j = 0; j < adj_cnt; j++) {
			cin >> adj_id;
			v[i].push_back(adj_id);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	input();
	solution();

	return 0;
}
