#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int y;
	int x;
	int flag;
};

int n, m, t;
int MAP[101][101];

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

int res1 = -1;
int res2 = -1;
int res3 = -1;
Node Pos;

void bfs(Node s) {

	int visited[101][101] = { 0 };
	queue<Node> q;

	q.push({ s.y, s.x});
	visited[s.y][s.x] = 1;

	while (!q.empty()) {

		Node now = q.front();
		q.pop();

		if (MAP[now.y][now.x] == 2) {
			res1 = visited[now.y][now.x] - 1;
			Pos = { now.y, now.x };
			break;
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
			if (visited[ny][nx] != 0) continue;
			if (MAP[ny][nx] == 1) continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny, nx });
			
		}
	}
}

void bfs2(Node s) {

	int visited[101][101] = { 0 };
	queue<Node> q;

	q.push({ s.y, s.x });
	visited[s.y][s.x] = 1;

	while (!q.empty()) {

		Node now = q.front();
		q.pop();

		if (now.y==n-1 && now.x==m-1) {
			res2 = visited[now.y][now.x] - 1;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
			if (visited[ny][nx] != 0) continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny, nx });

		}
	}

}

void bfs3(Node s) {

	int visited[101][101] = { 0 };
	queue<Node> q;

	q.push({ s.y, s.x });
	visited[s.y][s.x] = 1;

	while (!q.empty()) {

		Node now = q.front();
		q.pop();

		if (now.y == n - 1 && now.x == m - 1) {
			res3 = visited[now.y][now.x] - 1;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
			if (visited[ny][nx] != 0) continue;
			if (MAP[ny][nx] == 1) continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny, nx });

		}
	}
}

int main() {

	cin >> n >> m >> t;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> MAP[i][j];
		}
	}

	// 출발지부터 검까지의 거리
	bfs({ 0, 0});

	// 검에서부터 도착지까지의 거리
	bfs2(Pos);

	// 검 안 찾고 가는 방법
	bfs3({ 0, 0 });
	 

	if (res1 == -1 && res2 == -1 && res3 == -1) cout << "Fail\n";
	else if (res1 == -1 && res2 == -1) {
		if (res3 <= t) cout << res3 << "\n";
		else cout << "Fail\n";
	}
	else if (res3 == -1) {
		if (res1 == -1 || res2 == -1) cout << "Fail\n";
		else {
			if (res1 + res2 <= t) cout << res1 + res2 << "\n";
			else cout << "Fail\n";
		}
	}
	else {
		int res = min(res1 + res2, res3);
		if (res <= t) cout << res << "\n";
		else cout << "Fail\n";
	}

	return 0;
}
