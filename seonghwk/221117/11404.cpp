#define MAX_DIST 10'000'000
// 버스 한 번 비용이 100'000 이하이므로
// 최대 100개의 도시에서, 모든 도시 들러서 방문할때 99번 탑승하므로
// 최대 거리는 100'000 * 100으로 두어도 충분

#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<vector<int>> adj;

void input() {
  cin >> n;
  cin >> m;
  adj = vector<vector<int>>(n + 1, vector<int>(n + 1, MAX_DIST));
  int a, b, c;
  for (int i = 1; i <= m; i++) {
    cin >> a >> b >> c;
    adj[a][b] = min(adj[a][b], c);
  }
}

void floyd() {
  for (int i = 1; i <= n; i++) adj[i][i] = 0;

  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
      }
    }
  }
}

void solution() {
  floyd();
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (adj[i][j] == MAX_DIST) {
        cout << "0 ";
      } else {
        cout << adj[i][j] << " ";
      }
    }
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  input();
  solution();

  return 0;
}