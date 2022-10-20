#include <iostream>
#include <queue>
using namespace std;

// 바이러스 1 ~ K
// 1초마다 상하좌우 증식 -> 낮은 번호부터 증식
// 이미 바이러스 있는 칸에는 증식 X
// ==> S초가 지난 후 (Y,X)에 존재하는 바이러스 종류는?

struct Virus {
	int y, x, num;
};

bool operator<(Virus a, Virus b) {
	// 번호 작은 게 우선
	if (a.num < b.num) return false;
	if (a.num > b.num) return true;
	return false;
}

int N, K;
int MAP[201][201];
int S, Y, X;

priority_queue<Virus> pq1;
priority_queue<Virus> pq2;
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] > 0)
				pq1.push({ i,j,MAP[i][j] });
		}
	}
	cin >> S >> Y >> X;

	// BFS
	// 1초 동안 모든 종류의 바이러스 번식이 일어나야 함 --> pq 2개로 **
	int t = 0;
	while (1) {
		// ** S의 범위 0도 포함하므로 처음에 체크해 줘야 함 **
		if (t == S) {
			cout << MAP[Y][X];
			break;
		}
		// 1초
		while (!pq1.empty()) {
			Virus now = pq1.top();
			pq1.pop();

			for (int i = 0; i < 4; i++) {
				int ny = now.y + ydir[i];
				int nx = now.x + xdir[i];
				if (ny < 1 || nx < 1 || ny > N || nx > N)
					continue;
				// 이미 바이러스가 있으면 패스
				if (MAP[ny][nx] > 0)
					continue;
				MAP[ny][nx] = now.num;
				pq2.push({ ny,nx,MAP[ny][nx] });
			}
		}
		t++;
		if (t == S) {
			cout << MAP[Y][X];
			break;
		}
		// 2초
		while (!pq2.empty()) {
			Virus now = pq2.top();
			pq2.pop();

			for (int i = 0; i < 4; i++) {
				int ny = now.y + ydir[i];
				int nx = now.x + xdir[i];
				if (ny < 1 || nx < 1 || ny > N || nx > N)
					continue;
				// 이미 바이러스가 있으면 패스
				if (MAP[ny][nx] > 0)
					continue;
				MAP[ny][nx] = now.num;
				pq1.push({ ny,nx,MAP[ny][nx] });
			}
		}
		t++;
	}

	return 0;
}
