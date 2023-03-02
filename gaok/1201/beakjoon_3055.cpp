#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Node {
	int y;
	int x;
};

int r, c;
string MAP[51][51];
int water[51][51] = { 0 };
vector<Node> w;
Node Start;
Node End;

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

int res = -1;
void bfs(Node s) {
	int visited[51][51] = { 0 };
	visited[s.y][s.x] = 1;
	queue<Node> q;
	q.push(s);

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		// 비버에 도달했는지 체크
		if (now.y == End.y && now.x == End.x) {
			res = visited[now.y][now.x];
			break;
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= r || nx < 0 || nx >= c) continue;
			if (visited[ny][nx] != 0) continue;
			if (MAP[ny][nx] == "X") continue;
			if (water[ny][nx] <= visited[now.y][now.x] + 1) continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny, nx });
		}
	}
}


void move_water() {

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			water[i][j] = 2134567890;
		}
	}

	queue<Node> q;
	
	for (int i = 0; i < w.size(); i++) {
		water[w[i].y][w[i].x] = 1;
		q.push({ w[i].y, w[i].x });
	}

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= r || nx < 0 || nx >= c) continue;
			if (water[ny][nx] != 2134567890) continue;
			if (MAP[ny][nx] == ".") {
				water[ny][nx] = water[now.y][now.x] + 1;
				q.push({ ny, nx });
			}
		}
	}
}


int main() {

	cin >> r >> c;

	for (int i = 0; i < r; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < c; j++) {
			MAP[i][j] = str[j];
			if (MAP[i][j] == "*") {
				w.push_back({ i, j });
			}
			if (MAP[i][j] == "S") {
				Start = { i, j };
			}
			if (MAP[i][j] == "D") {
				End = { i, j };
			}
		}
	}
	

	move_water();

	bfs(Start);

	if (res == -1) cout << "KAKTUS";
	else cout << res-1;
}
