#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Coord {
	int y, x;
	int cnt;
};

struct Record {
	int cntV;
	int cntK;
};

int K, W, H;
int MAP[201][201];
Record visited[201][201];

void input() {
	cin >> K >> W >> H;

	for (int y = 1; y <= H; y++)
		for (int x = 1; x <= W; x++)
			cin >> MAP[y][x];
}

int bfs() {
	queue<Coord> q;

	visited[1][1] = { 1,0 };

	q.push({ 1,1,0 });

	while (!q.empty()) {
		Coord now = q.front();
		q.pop();

		if (now.y == H && now.x == W) {
			return visited[H][W].cntV - 1;
		}

		int dy[] = { -1,1,0,0,-2,-1,1,2,2,1,-1,-2 };
		int dx[] = { 0,0,-1,1,-1,-2,-2,-1,1,2,2,1 };

		for (int i = 0; i < 12; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			int ncnt = now.cnt;
			if (i > 3)
				ncnt++;

			if (ny < 1 || ny>H || nx <1 || nx>W)
				continue;

			if (MAP[ny][nx] == 1)
				continue;

			if (visited[ny][nx].cntK <= ncnt && visited[ny][nx].cntV > 0)
				continue;

			if (ncnt > K)
				continue;

			visited[ny][nx].cntK = ncnt;
			visited[ny][nx].cntV = visited[now.y][now.x].cntV + 1;
			q.push({ ny,nx,ncnt });
		}
	}

	return -1;
}

void solution() {
	int ans = bfs();

	cout << ans;
}

int main() {
	input();
	solution();

	return 0;
}