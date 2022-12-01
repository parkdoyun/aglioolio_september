#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Coord {
	int y, x;
};

int N, M, T;
int MAP[100][100];
int dist[100][100];
Coord sword = { 0,0 };

void input() {
	cin >> N >> M >> T;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < M; x++) {
			cin >> MAP[y][x];
			if (MAP[y][x] == 2) {
				sword.y = y;
				sword.x = x;
			}
		}
			
}

void bfs() {
	queue<Coord> q;

	dist[0][0] = 1;

	q.push({ 0,0 });

	while (!q.empty()) {
		Coord now = q.front();
		q.pop();

		int dy[] = { -1,0,1,0 };
		int dx[] = { 0,1,0,-1 };

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= M)
				continue;

			if (MAP[ny][nx] == 1)
				continue;

			if (dist[ny][nx] > 0)
				continue;

			dist[ny][nx] = dist[now.y][now.x] + 1;
			q.push({ ny,nx });
		}
	}
}

void solve() {
	int distP = 2134567890;
	int distSwordP = 2134567890;

	bfs();

	if (dist[N - 1][M - 1] == 0 && dist[sword.y][sword.x] == 0) {
		cout << "Fail\n";
		return;
	}

	if (dist[N - 1][M - 1] != 0) {
		distP = dist[N - 1][M - 1] - 1;
	}

	if (dist[sword.y][sword.x] != 0) {
		distSwordP = dist[sword.y][sword.x] - 1 + (N - 1 - sword.y + M - 1 - sword.x);
	}

	int ans = min(distP, distSwordP);

	if (ans <= T)
		cout << ans << "\n";
	else
		cout << "Fail\n";
}

int main() {
	input();
	solve();

	return 0;
}