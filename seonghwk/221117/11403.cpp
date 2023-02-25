#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> adj;
vector<vector<int>> via;

void input() {
  cin >> N;
  adj = vector<vector<int>>(N, vector<int>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> adj[i][j];
    }
  }
}

void floyd() {
  for (int i = 0; i < N; i++) adj[i][i] = 0;
  via = vector<vector<int>>(N, vector<int>(N, -1));

  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
      }
    }
  }
}

void solution() {
  floyd();
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << adj[i][j] << " ";
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