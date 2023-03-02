#include <limits.h>

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int to, cost;
};

bool operator<(Edge a, Edge b) { return a.cost > b.cost; }

int N, M, X;

vector<vector<Edge>> v;

void input() {
  cin >> N >> M >> X;
  v = vector<vector<Edge>>(N + 1, vector<Edge>());
  int from, to, cost;
  for (int i = 0; i < M; i++) {
    cin >> from >> to >> cost;
    v[from].push_back({to, cost});
  }
}

vector<int> dijkstra(int start, int end) {
  vector<int> dist(N + 1, INT_MAX);
  priority_queue<Edge> pq;

  dist[start] = 0;
  pq.push({start, dist[start]});

  while (!pq.empty()) {
    Edge now = pq.top();
    pq.pop();

    if (dist[now.to] < now.cost) continue;
    if (now.to == end) break;

    for (int i = 0; i < v[now.to].size(); i++) {
      Edge next = v[now.to][i];
      if (dist[next.to] <= dist[now.to] + next.cost) continue;
      dist[next.to] = dist[now.to] + next.cost;
      pq.push({next.to, dist[next.to]});
    }
  }
  return dist;
}

void solution() {
  vector<vector<int>> dist(2, vector<int>(N + 1));
  for (int i = 1; i <= N; i++) {
    vector<int> departure = dijkstra(i, X);
    dist[0][i] = departure[X];
  }
  vector<int> arrival = dijkstra(X, -1);
  for (int i = 1; i <= N; i++) {
    dist[1][i] = arrival[i];
  }
  int max_dist = 0;
  for (int i = 1; i <= N; i++) {
    max_dist = max(max_dist, dist[0][i] + dist[1][i]);
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

/*
유향 그래프
도로에 id 있다
N개 도시, M개 도로, X에서 집결
오고 가는데 가장 많은 시간 소비하는 학생
1. 각 도시에서 X로 가는데 걸리는 최소 시간
  -> 각 도시에서 다익스트라 수행하는데, X 거리 확정하면 중단
2. X에서 각 도시로 가는데 걸리는 최소 시간 -> dijkstra
  -> 모든 도시 방문 거리 확정해야함
3. dist 배열에서 1, 2를 통해 구한 값의 최대값 찾기
*/