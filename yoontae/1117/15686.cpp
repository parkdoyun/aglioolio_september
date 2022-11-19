#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Coord {
	int y, x;
};

int N, M;
int MAP[55][55];
vector <Coord> chicken;
vector <Coord> chosen;
int ans = 2134567890;;

void input() {
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> MAP[y][x];
			if (MAP[y][x] == 2)
				chicken.push_back({ y,x });
		}
	}
}

int bfs() {
	queue<Coord> q;

	int visited[55][55] = { 0 };

	for (auto m : chosen) {
		visited[m.y][m.x] = 1;
		q.push(m);
	}

	while (!q.empty()) {
		Coord now = q.front();
		q.pop();

		int dy[] = { -1,0,1,0 };
		int dx[] = { 0,1,0,-1 };

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N)
				continue;

			if (visited[ny][nx] > 0)
				continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx });
		}
	}

	int totalDist = 0;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (MAP[y][x] == 1) {
				totalDist += visited[y][x] - 1;
			}
		}
	}

	return totalDist;
}

void dfs(int level) {

	if (chosen.size() == M) {
		ans = min(ans, bfs());
		return;
	}

	if (level == (int)(chicken.size()))
		return;

	chosen.push_back(chicken[level]);
	dfs(level + 1);
	chosen.pop_back();
	dfs(level + 1);
}

void solve() {
	dfs(0);

	cout << ans;
}

int main() {
	input();
	solve();

	return 0;
}