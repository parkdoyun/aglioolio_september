#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
	int y;
	int x;
};

int n, m;
int MAP[301][301];
int copy_map[301][301];
vector<Node> ice;

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
void count_zero() {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			copy_map[i][j] = 0;
		}
	}
	
	for (int i = 0; i < ice.size(); i++) {
		Node now = ice[i];
		int cnt = 0;
		for (int j = 0; j < 4; j++) {
			int ny = now.y + dy[j];
			int nx = now.x + dx[j];

			if (MAP[ny][nx] == 0) cnt++;
		}
		copy_map[now.y][now.x] = MAP[now.y][now.x] - cnt;
		if (copy_map[now.y][now.x] < 0) copy_map[now.y][now.x] = 0;
	}

	ice.clear();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			MAP[i][j] = copy_map[i][j];
			if (MAP[i][j] != 0) ice.push_back({ i, j });
		}
	}
}


bool isConnected() {
	int visited[301][301] = { 0 };
	queue<Node> q;

	q.push(ice[0]);
	visited[ice[0].y][ice[0].x] = 1;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (MAP[ny][nx] == 0) continue;
			if (visited[ny][nx] != 0) continue;
			if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
			visited[ny][nx] = 1;
			q.push({ ny, nx });
		}
	}

	for (int i = 0; i < ice.size(); i++) {
		if (visited[ice[i].y][ice[i].x] == 0) return false;
	}
	return true;
}

int main() {

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] != 0) ice.push_back({ i, j });
		}
	}

	int t = 0;
	while (true) {
		int flag = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (MAP[i][j] != 0) {
					flag = 1;
					break;
				}
			}
		}

		if (flag == 0) {
			cout << 0;
			break;
		}

		t++;
		count_zero();

		bool res = isConnected();
		if (res == false) {
			cout << t;
			break;
		}
	}
	
}
