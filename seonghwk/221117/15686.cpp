#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
  int y, x;
};

struct Dist {
  int id, dist;
};

bool operator<(Dist a, Dist b) {
  if (a.dist < b.dist) return true;
  if (a.dist > b.dist) return false;
  return false;
}

int N, M;
int board[50][50];
vector<Node> house;
vector<Node> chicken;
int flag[13];
vector<Dist> v[100];
int min_dist_sum = 2147483647;

int getCityDist() {
  int dist_sum = 0;
  for (int i = 0; i < house.size(); i++) {
    for (int j = 0; j < v[i].size(); j++) {
      Dist now = v[i][j];
      if (flag[now.id] == 0) continue;
      dist_sum += now.dist;
      break;
    }
  }
  if (dist_sum == 0) dist_sum = 2147483647;
  return dist_sum;
}

void dfs(int level, int cnt) {
  // base case
  if (cnt > M) return;
  if (level == chicken.size()) {
    min_dist_sum = min(min_dist_sum, getCityDist());
    return;
  }
  // recursive case
  flag[level] = 1;
  dfs(level + 1, cnt + 1);
  flag[level] = 0;
  dfs(level + 1, cnt);
}

void solution() {
  dfs(0, 0);
  cout << min_dist_sum;
}

int getDist(int h_id, int c_id) {
  Node h = house[h_id];
  Node c = chicken[c_id];

  return abs(h.y - c.y) + abs(h.x - c.x);
}

void input() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> board[i][j];
      if (board[i][j] == 1) house.push_back({i, j});
      if (board[i][j] == 2) chicken.push_back({i, j});
    }
  }

  for (int i = 0; i < house.size(); i++) {
    for (int j = 0; j < chicken.size(); j++) {
      v[i].push_back({j, getDist(i, j)});
    }
    sort(v[i].begin(), v[i].end());
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

/*
N-by-N board
0 빈칸, 1 집, 2 치킨
집 : [1, 2N], 치킨 : [M, 13]

치킨거리 : 집과 가장 가까운 치킨 집 사이의 거리

치킨집 최대 M개만 생존, 나머지 폐업
치킨거리 최솟값

고정된 값
- 각각의 집에서 각각의 치킨집으로의 치킨거리

변하는 값
- 생존한 치킨집

치킨집을 고르는 경우 -> 1~M개의 조합
*/