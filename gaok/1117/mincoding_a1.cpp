#include <iostream>
#include <vector>
using namespace std;

struct Node {
	int y;
	int x;
};

int h, w;
int MAP[16][16];

vector<Node> path;

// 짝수 열 : 윗 대각선
int dy[6] = { -1, 1, 0, 0, -1, -1 };
int dx[6] = { 0, 0, -1, 1, -1, 1 };

// 홀수 열 : 밑 대각선
int dy2[6] = { -1, 1, 0, 0, 1, 1 };
int dx2[6] = { 0, 0, -1, 1, -1, 1 };

int visited[16][16];
int maxCost = -2134567890;
void dfs(int y, int x, int cnt, int sum) {

	if (cnt == 3) {
		int maxNode = -2134567890;
		for (int i = 0; i < path.size(); i++) {
			Node now = path[i];
			int nexty;
			int nextx;
			for (int j = 0; j < 6; j++) {
				if (now.x % 2 == 0) {
					nexty = now.y + dy[j];
					nextx = now.x + dx[j];
				}
				if (now.x % 2 == 1) {
					nexty = now.y + dy2[j];
					nextx = now.x + dx2[j];
				}

				if (nexty < 0 || nexty >= h || nextx < 0 || nextx >= w) continue;
				if (visited[nexty][nextx] != 0) continue;

				if (maxNode < MAP[nexty][nextx]) maxNode = MAP[nexty][nextx];
			}
		}
		sum += maxNode;
		if (maxCost < sum) maxCost = sum;
		return;
	}

	int ny;
	int nx;
	for (int i = 0; i < 6; i++) {

		if (x % 2 == 0) {
			ny = y + dy[i];
			nx = x + dx[i];
		}

		else {
			ny = y + dy2[i];
			nx = x + dx2[i];
		}
			
		if (ny < 0 || ny >= h || nx < 0 || nx >= w) continue;
		if (visited[ny][nx] != 0) continue;

		visited[ny][nx] = 1;
		path.push_back({ ny, nx });
		dfs(ny, nx, cnt+1, sum+MAP[ny][nx]);
		path.pop_back();
		visited[ny][nx] = 0;
	}

}

int main() {

	cin >> h >> w;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> MAP[i][j];
		}
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			visited[i][j] = 1;
			path.push_back({ i, j });
			dfs(i, j, 1, MAP[i][j]);
			path.pop_back();
			visited[i][j] = 0;
		}
	}

	cout << maxCost;


	return 0;
}
