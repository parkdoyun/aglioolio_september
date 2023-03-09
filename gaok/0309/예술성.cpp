#include <iostream>
#include <queue>
using namespace std;

/* 
삼성전자 기출문제 - 예술성
1. 그룹 나누기 -> bfs
2. 예술점수 = 모든 그룹 쌍의 조화로움의 합 
-> (그룹 a에 속한 칸의 수 + 그룹 b에 속한 칸의 수) x 그룹 a를 이루고 있는 숫자 값 x 그룹 b를 이루고 있는 숫자값 x 그룹 a와 그룹 b가 서로 맞닿아있는 변의 수 
-> 맞닿아있는 경우에만 계산 
3. 회전 
*/

struct Node {
	int y;
	int x;
};

int n;
int MAP[30][30];
int visited[30][30];
int group_id = 1;
int group[30][30];
int group_cnt[1000];  // 그룹에 속한  칸의 수

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int cnt = 0;

int MAP_copy[30][30];

void input() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
		}
	}
}

void make_group(int row, int col) {
	queue<Node> q;
	q.push({ row, col });
	visited[row][col] = 1;
	cnt = 1;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			if (visited[ny][nx] != 0) continue;
			if (MAP[ny][nx] != MAP[row][col]) continue;

			visited[ny][nx] = 1;
			group[ny][nx] = group_id;
			cnt++;
			q.push({ ny, nx });
		}
	}
}

int calc() {
	int res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];

				if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
				if (group[ny][nx] == group[i][j]) continue;

				// 다른 그룹이라면 계산 시작
				res += (group_cnt[group[i][j]] + group_cnt[group[ny][nx]]) * MAP[i][j] * MAP[ny][nx];
			}
		}
	}
	return res;
}

void copy_map() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			MAP_copy[i][j] = MAP[i][j];
		}
	}
}

void rotate_X() {

	copy_map();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			MAP_copy[n-1-j][i] = MAP[i][j];
		}
	}
}

void rotate(int sr, int er, int sc, int ec) {

	for (int i = sr; i < er; i++) {
		for (int j = sc; j < ec; j++) {

			int r = i - sr;
			int c = j - sc;

			int nr = c;
			int nc = n/2 - 1 - r;

			MAP_copy[nr + sr][nc + sc] = MAP[i][j];

		}
	}
}


void init() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			MAP[i][j] = MAP_copy[i][j];
			visited[i][j] = 0;
			group[i][j] = 0;
		}
	}

	for(int i=0; i<1000; i++){
		group_cnt[i] = 0;
	}

	group_id = 1;
}

int main() {

	input();
	int ans = 0;
	for (int t = 0; t <= 3; t++) {
		// 그룹 나누기 
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (visited[i][j] != 0) continue;
				group[i][j] = group_id;
				make_group(i, j);
				group_cnt[group_id] = cnt;
				group_id++;
			}
		}

		// 예술 점수 계산
		int res = calc() / 2;
		ans += res;

		// 회전
		rotate_X();

		rotate(0, n / 2, 0, n / 2);
		rotate(0, n / 2, n / 2 + 1, n);
		rotate(n / 2 + 1, n, 0, n / 2);
		rotate(n / 2 + 1, n, n / 2 + 1, n);

		init();
	}

	cout << ans;

	return 0;
}
