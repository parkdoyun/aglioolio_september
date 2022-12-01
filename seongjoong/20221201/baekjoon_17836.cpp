#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

struct Node {
	int y, x, dist, gram;
};

int N, M, T;
int MAP[101][101];
int visited[101][101][2]; // [0]: 그람 찾기 전, [1]: 후
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

void bfs() {
	queue<Node> q;
	q.push({ 1,1,0,0 });
	visited[1][1][0] = 1;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		// 제한 시간 넘어가면 패스
		// *** 1부터 시작하므로 등호 포함 X ***
		if (now.dist > T)
			continue;

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny<1 || nx<1 || ny>N || nx>M)
				continue;
			if (visited[ny][nx][now.gram])
				continue;
			if (MAP[ny][nx] == 1 && now.gram == 0)
				continue;
			
			// 그람을 찾았다!
			if (MAP[ny][nx] == 2) {
				visited[ny][nx][1] = visited[now.y][now.x][0] + 1;
				q.push({ ny,nx,visited[ny][nx][1],1 });
			}
			else {
				visited[ny][nx][now.gram] = visited[now.y][now.x][now.gram] + 1;
				q.push({ ny,nx,visited[ny][nx][now.gram],now.gram });
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			cin >> MAP[i][j];

	bfs();

	if (visited[N][M][0] && visited[N][M][1])
		cout << min(visited[N][M][0], visited[N][M][1]) - 1;
	else if (visited[N][M][0])
		cout << visited[N][M][0] - 1;
	else if (visited[N][M][1])
		cout << visited[N][M][1] - 1;
	else
		cout << "Fail";

	return 0;
}
