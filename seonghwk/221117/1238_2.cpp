// solved with Floyd-Warshall Algorithm
// took longer time than Dijkstra
#define MAX_DIST 10'000'000

#include <iostream>
#include <vector>

using namespace std;

int N, M, X;
vector<vector<int>> adj;

void input() {
  cin >> N >> M >> X;
  adj = vector<vector<int>>(N + 1, vector<int>(N + 1, MAX_DIST));
  int a, b, c;
  for (int i = 1; i <= M; i++) {
    cin >> a >> b >> c;
    adj[a][b] = min(adj[a][b], c);
  }
}

void floyd() {
  for (int i = 1; i <= N; i++) adj[i][i] = 0;

  for (int k = 1; k <= N; k++) {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
      }
    }
  }
}

void solution() {
  floyd();
  int max_dist = 0;
  for (int i = 1; i <= N; i++) {
    max_dist = max(max_dist, adj[i][X] + adj[X][i]);
  }
  cout << max_dist;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  input();
  solution();

  return 0;
}