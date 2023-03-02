#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
  int y, x;
};

int N, M;
vector<vector<int>> board;
vector<vector<int>> visited;

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

void input() {
  cin >> N >> M;
  board = vector<vector<int>>(N, vector<int>(M));
  string row;
  for (int i = 0; i < N; i++) {
    cin >> row;
    for (int j = 0; j < M; j++) {
      board[i][j] = row[j] - '0';
    }
  }
}

void bfs() {
  visited = vector<vector<int>>(N, vector<int>(M));
  queue<Node> q;

  visited[0][0] = 1;
  q.push({0, 0});

  while (!q.empty()) {
    Node now = q.front();
    q.pop();

    for (int i = 0; i < 4; i++) {
      int ny = now.y + dy[i];
      int nx = now.x + dx[i];
      if (!(0 <= ny && ny < N) || !(0 <= nx && nx < M)) continue;
      if (board[ny][nx] == 0) continue;
      if (visited[ny][nx] != 0) continue;
      visited[ny][nx] = visited[now.y][now.x] + 1;
      q.push({ny, nx});
    }
  }
}

void solution() {
  bfs();
  cout << visited[N - 1][M - 1] << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  input();
  solution();

  return 0;
}