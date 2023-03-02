#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int y;
	int x;
	int d;
};

bool operator<(Node a, Node b) {
	if (a.d < b.d) return false;
	if (a.d > b.d) return true;
	if (a.y < b.y) return false;
	if (a.y > b.y) return true;
	if (a.x < b.x) return false;
	if (a.x > b.x) return true;
	return true;
}

Node Start;
int n;
int level = 2;
int guage = 0;
int MAP[21][21];

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

priority_queue<Node> pq;
void bfs(int y, int x) {

	int visited[21][21] = { 0 };
	queue<Node> q;
	q.push({ y, x, 1 });
	visited[y][x] = 1;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			if (visited[ny][nx] != 0) continue;
			if (level < MAP[ny][nx]) continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny, nx, visited[ny][nx] });
			if (MAP[ny][nx] != 0 && (level > MAP[ny][nx])) {
				pq.push({ ny, nx, visited[ny][nx]-1 });
			}
		}
	}

}

int main() {

	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 9) Start = { i, j, 1 };
		}
	}

	int time = 0;
	while (true) {
		bfs(Start.y, Start.x);

		if (pq.size() == 0) break;
		Node next = pq.top();
		time += next.d;
		guage += 1;
		if (level == guage) {
			guage = 0;
			level += 1;
		}

		MAP[Start.y][Start.x] = 0;
		MAP[next.y][next.x] = 0;
		Start = { next.y, next.x };
		while (!pq.empty()) pq.pop();
		
	}
	
	
	cout << time << "\n";

	return 0;
}
