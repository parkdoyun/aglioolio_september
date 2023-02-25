#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
	int y;
	int x;
};

int MAP[51][51];

int n, m, r, c, l;
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

int visited[51][51];
int cnt = 0;

int dir[8][4] = {
	{0, 0, 0, 0},
	{1, 1, 1, 1},
	{1, 1, 0, 0},
	{0, 0, 1, 1},
	{1, 0, 0, 1},
	{0, 1, 0, 1},
	{0, 1, 1, 0},
	{1, 0, 1, 0}
};

bool isPossible(int target, int d) {
	int flip_d;
	if (d == 0) flip_d = 1;
	if (d == 1) flip_d = 0;
	if (d == 2) flip_d = 3;
	if (d == 3) flip_d = 2;

	if (dir[target][flip_d] == 1) return true;
	return false;
}

void bfs(int y, int x) {

	queue<Node> q;
	q.push({ y, x });
	visited[y][x] = 1;

	while (!q.empty()) {
		Node now = q.front();
		int type = MAP[now.y][now.x];
		q.pop();

		if (type == 0) continue;

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
			if (visited[ny][nx] != 0) continue;
			if (MAP[ny][nx] == 0) continue;

			if (dir[type][i] != 1) continue;
			if (!isPossible(MAP[ny][nx], i)) continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny, nx });
			if (visited[ny][nx] <= l) cnt += 1;
		}
	}

}

void init() {
	cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = 0;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;

	for (int testcase = 0; testcase < t; testcase++) {

		cin >> n >> m >> r >> c >> l;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> MAP[i][j];
			}
		}

		bfs(r, c);

		cout << "#" << testcase + 1 << " " << cnt + 1 << "\n";

		init();
	}

	return 0;
}
