#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
struct Pos {
    int y;
    int x;
    int d;
    int cnt;
};
 
struct Info {
    int cnt;
    int d;
};
 
bool operator<(Info a, Info b) {
    if (a.cnt < b.cnt) return true;
    if (a.cnt > b.cnt) return false;
    return false;
}
 
int dy[] = { 0, -1, 1, 0, 0 };
int dx[] = { 0, 0, 0, -1, 1 };
 
int n, m, k;
vector<Pos> micros;
priority_queue<Info> pq[101][101];
int all_cnt = 0;
int reverse_dir(int d) {
    if (d == 1) return 2;
    if (d == 2) return 1;
    if (d == 3) return 4;
    if (d == 4) return 3;
}
 
vector<Pos> move_micro() {
    all_cnt = 0;
 
    for (int i = 0; i < micros.size(); i++) {
        Pos now = micros[i];
        if (now.y == -1) continue;  // 미생물이 이미 없는 경우 
 
        int ny = now.y + dy[now.d];
        int nx = now.x + dx[now.d];
        int d = now.d;
        if (ny == 0 || ny == n - 1 || nx == 0 || nx == n - 1) {
            d = reverse_dir(now.d);
            now.cnt = now.cnt / 2;
            if (now.cnt == 0) micros[i] = { -1, -1, -1, -1 };
        }
        micros[i] = { ny ,nx, d, now.cnt };
         
        if (now.cnt > 0) {
            pq[ny][nx].push({ now.cnt, d });
        }
         
    }
 
    vector<Pos> micros_temp;
    for (int i = 0; i < micros.size(); i++) {
        Pos now = micros[i];
        if (now.y == -1) continue;
 
        int y = now.y;
        int x = now.x;
 
        if (pq[y][x].empty()) continue;
        int cnt = pq[y][x].top().cnt;
        int d = pq[y][x].top().d;
        pq[y][x].pop();
 
        while (!pq[y][x].empty()) {
            cnt += pq[y][x].top().cnt;
            pq[y][x].pop();
        }
        micros_temp.push_back({ y, x, d, cnt });
        all_cnt += cnt;
    }
 
    return micros_temp;
}
 
int main() {
 
    int t;
    cin >> t;
 
    for (int testcase = 0; testcase < t; testcase++) {
        cin >> n >> m >> k;
        for (int i = 0; i < k; i++) {
            int y, x, cnt, d;
            cin >> y >> x >> cnt >> d;
            micros.push_back({ y, x, d, cnt });
        }
 
        for (int i = 0; i < m; i++) {
            vector<Pos> res = move_micro();
            micros = res;
        }
 
        cout << "#"<<testcase+1<<" " <<all_cnt << "\n";
 
        micros.clear();
         
    }
 
    return 0;
}
