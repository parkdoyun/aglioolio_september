#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

struct Coord {
	int y, x;
	int cnt; // 말처럼 움직인 횟수
};

int K, W, H;
int MAP[200][200];
int visited[31][200][200];
// visited[n][y][x] : (y,x)에 말처럼 n번 이동해서 도착. ***

// 같은 좌표라도 능력을 몇 번 사용해서 왔는지에 따라 다양한 경우가 발생.
// --> visited를 1차원 배열로 처리하면 무조건 "최소한으로 해당 좌표까지 도달하는 경우만" 기록된다.
// ex)
// 마지막에 도착지에 도달하기 위해 말처럼 뛰어서 벽을 넘어야 하는 경우가 있을 수 있는데,
// 이전에 K번만큼 이미 써버려서 -1을 리턴한다.

int ydir[] = { -2,-2,-1,-1,1,1,2,2,-1,1,0,0 };
int xdir[] = { -1,1,-2,2,-2,2,-1,1,0,0,-1,1 };
// 0~7 : 말, 8~11 : 원숭이

int bfs() {
	queue<Coord> q;
	q.push({ 0,0,0 });

	visited[0][0][0] = 1;

	while (!q.empty()) {
		Coord now = q.front();
		q.pop();

		int st = 0;
		if (now.cnt >= K)
			st = 8;
		for (int i = st; i < 12; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny < 0 || nx < 0 || ny >= H || nx >= W)
				continue;
			if (MAP[ny][nx] == 1)
				continue;
			// 다음 좌표를 말처럼 이동해서 가는 경우
			if (0 <= i && i <= 7) {
				int nextCnt = now.cnt + 1;
				if (visited[nextCnt][ny][nx])
					continue;
				visited[nextCnt][ny][nx] = visited[now.cnt][now.y][now.x] + 1;
				q.push({ ny,nx,nextCnt });
			}
			else {
				if (visited[now.cnt][ny][nx])
					continue;
				visited[now.cnt][ny][nx] = visited[now.cnt][now.y][now.x] + 1;
				q.push({ ny,nx,now.cnt });
			}
		}
	}

	int ans = 2134567890;
	for (int i = 0; i <= K; i++) {
		// 도착점까지 갈 수 있고, 지금 최소값보다 작으면 갱신
		if (visited[i][H - 1][W - 1] != 0 && visited[i][H - 1][W - 1] - 1 < ans)
			ans = visited[i][H - 1][W - 1] - 1;
	}
	// 한 번도 갱신이 안됐으면 도착지까지 갈 수 없다는 뜻.
	if (ans == 2134567890)
		ans = -1;

	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> K >> W >> H;
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			cin >> MAP[i][j];

	cout << bfs();

	return 0;
}
