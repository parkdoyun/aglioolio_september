#include <iostream>
#include <queue>
using namespace std;

// 스노우맨 - 좌우 땅이 있는 곳으로만 이동 
// 땅이 없는 곳은 좌우로 이동 불가능
// 수직이동 
// 한칸 이동할때마다 게이지 1씩 차오름, LIMIT 넘으면 녹아서 죽음
// 땅을 밟으면다시 게이지는 0으로 초기화
// 최소 LIMIT 출력 

struct Node {
	int y;
	int x;
	int guage;
	int maxGuage;
};

int n, m;
int MAP[51][51];
Node Start;
Node End;

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

int bfs(int y, int x) {

	queue<Node> q;
	int visited[51][51];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = 1e9;
		}
	}

	q.push({ y, x, 0, 0 });
	visited[y][x] = 0;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		if (MAP[now.y][now.x] != 0) now.guage = 0;
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
			if (i == 0 || i == 1) {
				if (visited[ny][nx] <= max(now.guage, now.maxGuage)) continue;
				visited[ny][nx] = max(now.guage, now.maxGuage);
				q.push({ ny, nx, now.guage + 1, visited[ny][nx] });
			}
			else {
				if (MAP[ny][nx] == 0 || MAP[now.y][now.x]==0) continue;
				if (visited[ny][nx] <= now.maxGuage) continue;
				visited[ny][nx] = now.maxGuage;
				q.push({ ny, nx, now.guage, visited[ny][nx] });
			}
		}
	}
	return visited[End.y][End.x];
}

int main() {

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> MAP[i][j];

			if (MAP[i][j] == 2) {
				Start = { i, j };
			}
			else if (MAP[i][j] == 3) {
				End = { i, j };
			}
		}
	}

	int res = bfs(Start.y, Start.x);
	cout << res+1 << "\n";

	return 0;
}
