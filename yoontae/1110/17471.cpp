#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N;
int population[11] = { 0 };
vector<int> edge[11];
int visited[11] = { 0 };
vector<int> districtA;
vector<int> districtB;
int minPopDiff = 2134567890;

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> population[i];

	for (int i = 1; i <= N; i++) {
		int num;
		cin >> num;

		for (int j = 0; j < num; j++) {
			int to;
			cin >> to;
			edge[i].push_back(to);
		}
	}
}

void bfs(int st) {
	queue<int> q;

	visited[st] = 1;

	q.push(st);

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		for (int i = 0; i < (int)(edge[now].size()); i++) {
			int next = edge[now][i];
			
			if (visited[next] == 1)
				continue;

			visited[next] = 1;
			q.push(next);
		}
	}
}

void checkConnected(int st, vector<int> district) {
	queue<int> q;

	visited[st] = 1;

	q.push(st);

	while (!q.empty()) {
		int now = q.front();
		q.pop();


		for (int i = 0; i < (int)(edge[now].size()); i++) {
			int next = edge[now][i];

			if (visited[next] == 1)
				continue;

			bool flag = true;
			for (int j = 0; j < (int)(district.size()); j++) {
				if (next == district[j]) {
					break;
				}
				if (j == (int)(district.size() - 1))
					flag = false;
			}

			if (!flag)
				continue;

			visited[next] = 1;
			q.push(next);
		}
	}
}

void dfs(int level) {
	if (level == N + 1) {
		if (districtA.size() == 0 || districtB.size() == 0)
			return;

		for (int i = 1; i <= N; i++) {
			visited[i] = 0;
		}

		checkConnected(districtA[0], districtA);
		checkConnected(districtB[0], districtB);

		bool connected = true;
		for (int i = 1; i <= N; i++) {
			if (visited[i] == 0) {
				connected = false;
				break;
			}
		}

		if (!connected)
			return;

		int popA = 0;
		int popB = 0;

		for (int i = 0; i < (int)(districtA.size()); i++)
			popA += population[districtA[i]];

		for (int i = 0; i < (int)(districtB.size()); i++)
			popB += population[districtB[i]];

		minPopDiff = min(minPopDiff, abs(popA - popB));

		return;
	}

	districtA.push_back(level);
	dfs(level + 1);
	districtA.pop_back();

	districtB.push_back(level);
	dfs(level + 1);
	districtB.pop_back();
}

void solve() {
	int cntCity = 0;

	for (int i = 1; i <= N; i++) {
		if (visited[i] == 0) {
			bfs(i);
			cntCity++;
		}
	}

	if (cntCity > 2) {
		cout << -1;
		return;
	}
	else if (cntCity == 2) {
		for (int i = 1; i <= N; i++) {
			visited[i] = 0;
		}

		int disA = 0;
		int disB = 0;

		bfs(1);

		for (int i = 1; i <= N; i++) {
			if (visited[i] == 0)
				disA += population[i];
			else
				disB += population[i];
		}

		cout << abs(disA - disB);

		return;
	}
	else if (cntCity == 1) {
		dfs(1);
		cout << minPopDiff;
		
		return;
	}
}

int main() {
	input();
	solve();

	return 0;
}