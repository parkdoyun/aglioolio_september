#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <unordered_map>
using namespace std;

struct Coord {
	int y, x;
};

int N, M;
int MAP[8][8];
int copyMAP[8][8];
int visited[8][8];

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };
void virus() {
	queue<Coord> q;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (copyMAP[i][j] == 2) {
				q.push({ i,j });
				visited[i][j] = 1;
			}
		}
	}

	while (!q.empty()) {
		Coord now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M)
				continue;
			if (visited[ny][nx])
				continue;
			if (copyMAP[ny][nx] == 1)
				continue;
			visited[ny][nx] = 1;
			copyMAP[ny][nx] = 2;
			q.push({ ny,nx });
		}
	}
}

int check() {
	int cnt = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (copyMAP[i][j] == 0)
				cnt++;

	return cnt;
}

void solve() {
	int ans = -2134567890;
	// 벽 3개 세우기 -> 조합
    // ** 순열/조합 코드 짜는 거 완벽하게 익힐 필요가 있음 **
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] != 0)
				continue;
			MAP[i][j] = 1;
			
			int stX = j; // ***
			for (int y = i; y < N; y++) {
				for (int x = stX; x < M; x++) {
					if (MAP[y][x] != 0)
						continue;
					MAP[y][x] = 1;

					int stC = x; // ***
					for (int r = y; r < N; r++) {
						for (int c = stC; c < M; c++) {
							if (MAP[r][c] != 0)
								continue;
							MAP[r][c] = 1;

							// 시뮬레이션 돌릴 맵 복사
							for (int row = 0; row < N; row++)
								for (int col = 0; col < M; col++)
									copyMAP[row][col] = MAP[row][col];
							// 초기화
							memset(visited, 0, sizeof(visited));
							// 바이러스 퍼뜨리기
							virus();
							// 안전구역 카운트
							int ret = check();
							if (ret > ans)
								ans = ret;

							// 세웠던 벽 해제
							MAP[r][c] = 0;
						}
						stC = 0; // ***
					}
					MAP[y][x] = 0;
				}
				stX = 0; // ***
			}
			MAP[i][j] = 0;
		}
	}

	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> MAP[i][j];

	// 맵의 크기가 작으므로 벽을 3개 세우는 모든 경우 체크.
	solve();

	return 0;
}
