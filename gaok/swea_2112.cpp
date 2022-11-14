#include <iostream>
#include <vector>
using namespace std;

int d, w, k;
int MAP[14][21];
int MAP_copy[14][21];

int minCnt = 2134567890;
vector<int> path;
bool isPass() {
	
	int flag = 0;
	for (int i = 0; i < w; i++) {
		int cnt = 1;
		int maxCnt = 0;
		int prev = MAP[0][i];
		for (int j = 1; j < d; j++) {
			if (prev == MAP[j][i]) cnt++;
			else {
				prev = MAP[j][i];
				cnt = 1;
			}
			maxCnt = max(maxCnt, cnt);
		}
		if (maxCnt < k) return false;
	}
	
	return true;
}

void change_row(int idx, int type) {
	for (int i = 0; i < w; i++) {
		MAP[idx][i] = type;
	}
}

void dfs(int level, int cnt) {

	if (minCnt <= cnt) return;

	if (level == d) {
		if (isPass()) {
			minCnt = min(minCnt, cnt);
		}
		return;
	}

	for (int j = 0; j < 2; j++) {
		change_row(level, j);
		dfs(level + 1, cnt + 1);
		for (int ii = 0; ii < w; ii++) {
			MAP[level][ii] = MAP_copy[level][ii];
		}
	}

	dfs(level + 1, cnt);
}

void init() {
	minCnt = 2134567890;
}

int main() {

	int t;
	cin >> t;

	for (int testcase = 0; testcase < t; testcase++) {
		
		cin >> d >> w >> k;

		for (int i = 0; i < d; i++) {
			for (int j = 0; j < w; j++) {
				cin >> MAP[i][j];
				MAP_copy[i][j]=MAP[i][j];
			}
		}

		if (isPass() || k==1) {
			cout << "#"<<testcase+1<<" " <<0 << "\n";
		}
		else {
			dfs(0, 0);
			cout << "#" << testcase + 1 << " " << minCnt << "\n";
		}

		init();

	}

	return 0;
}
