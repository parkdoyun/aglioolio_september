#include <iostream>
#include <vector>
using namespace std;

struct Node {
	int y;
	int x;
};

int MAP[11][11];
int limit[6];

int minCnt = 2134567890;

bool isPossible(int y, int x, int size) {
	for (int i = y; i < y + size; i++) {
		for (int j = x; j < x + size; j++) {
			if (MAP[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

void attach(int y, int x, int size) {
	for (int i = y; i < y + size; i++) {
		for (int j = x; j < x + size; j++) {
			MAP[i][j] = 0;
		}
	}
}

void detach(int y, int x, int size) {
	for (int i = y; i < y + size; i++) {
		for (int j = x; j < x + size; j++) {
			MAP[i][j] = 1;
		}
	}
}

bool check() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (MAP[i][j] != 0) return false;
		}
	}
	return true;
}

Node findNow() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (MAP[i][j] == 1) return { i, j };
		}
	}
}

void dfs(int cnt) {

	if (minCnt < cnt) return;
	
	if (check()) {
		if(minCnt > cnt) minCnt = cnt;
		return;
	}

	Node now = findNow();
	for (int i = 5; i > 0; i--) {
		if (limit[i] == 5) continue;
		if (now.y + i > 10 || now.x + i> 10) continue;
		if (isPossible(now.y, now.x, i) == false) continue;

		attach(now.y, now.x, i);
		limit[i] += 1;
		dfs(cnt + 1);
		limit[i] -= 1;
		detach(now.y, now.x, i);
	}

}

int main() {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> MAP[i][j];
		}
	}

	dfs(0);
	
	if (minCnt == 2134567890) minCnt = -1;
	cout << minCnt << "\n";

	return 0;
}
