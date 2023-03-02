#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int to, dist;
};

bool operator<(Edge& a, Edge& b) {
  if (a.dist < b.dist) return false;
  if (a.dist > b.dist) return true;
  return false;
}

int n, d, c;
vector<vector<Edge>> v;

void input() {
  cin >> n >> d >> c;
  int a, b, s;
  vector<vector<Edge>> v_connected(n + 1, vector<Edge>());
  for (int i = 0; i < d; i++) {
    cin >> a >> b >> s;
    v_connected[b].push_back({a, s});
  }
  v = v_connected;
}

void dijkstra(int& cnt, int& max_dist) {
  vector<int> dist(n + 1, 2147483647);
  priority_queue<Edge> pq;

  dist[c] = 0;
  pq.push({c, dist[c]});

  while (!pq.empty()) {
    Edge now = pq.top();
    pq.pop();

    if (dist[now.to] < now.dist) continue;

    for (int i = 0; i < v[now.to].size(); i++) {
      Edge next = v[now.to][i];
      if (dist[next.to] <= dist[now.to] + next.dist) continue;
      dist[next.to] = dist[now.to] + next.dist;
      pq.push({next.to, dist[next.to]});
    }
  }

  for (int i = 1; i <= n; i++) {
    if (dist[i] == 2147483647) continue;
    cnt++;
    max_dist = max(max_dist, dist[i]);
  }
}

void solution() {
  int cnt = 0;
  int max_dist = 0;
  dijkstra(cnt, max_dist);
  cout << cnt << " " << max_dist << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    input();
    solution();
  }

  return 0;
}

/*
a가 b에 의존 -> b가 감염되면 일정 시간 뒤 a도 감염
유향 그래프

해킹 된 컴퓨터 포함 총 몇대의 컴퓨터 감염?
걸리는 시간?

c부터 감염
a가 b를 의존, b가 감염되면 s초 후 a도 감염
*/