#include <iostream>
using namespace std;

int n, m, h;
int MAP[31][11];
int minCnt = 2134567890;

bool isCorrect() {

	for (int i = 1; i <= n; i++) {
		int way = i;
		for (int j = 1; j <= h; j++) {
			if (MAP[j][way] == 1) {
				way++;
			}
			else if (MAP[j][way - 1] == 1) {
				way--;
			}
		}
		if (way != i) return false;
	}
	return true;
}

void dfs(int a, int b, int cnt) {

	if (minCnt <= cnt) return;
	
	// i번 세로선의 결과가 i번이 나오는지 체크
	if (isCorrect()) {
		if(minCnt>cnt) minCnt = cnt;
		return;
	}

	if (cnt == 3) return;

	for (int i = a; i <= h; i++) {
		for (int j = b; j < n; j++) {
			if (MAP[i][j] == 1) continue;
			if (MAP[i][j - 1] == 1 || MAP[i][j + 1] == 1) continue;
			MAP[i][j] = 1;
			dfs(i, j, cnt+1);
			MAP[i][j] = 0;
		}
		b = 1;
	}

}

int main() {

	cin >> n >> m >> h;

	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		MAP[a][b] = 1;
	}

	dfs(1, 1, 0);
	if (minCnt == 2134567890) minCnt = -1;
	cout << minCnt << "\n";

	return 0;
}
