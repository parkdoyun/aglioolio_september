#include <iostream>
#include <queue>
using namespace std;
 
struct Node {
    int y;
    int x;
    int d;
    int cnt;
};
 
int sx;
int sy;
int ex;
int ey;
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
 
int bfs(int x, int y) {
 
    int visited[201][201][2] = { 0 };
 
    queue<Node> q;
     
    q.push({ y, x, 0, 1 });
    q.push({ y, x, 1, 1 });
    visited[y][x][0] = 1;
    visited[y][x][1] = 1;
 
    while (!q.empty()) {
        Node now = q.front();
        q.pop();
 
        int d = now.d;
         
        if (now.y == ey && now.x == ex) return now.cnt;
 
        if (d == 0) {
            // 세로 이동
            for (int i = 0; i < 2; i++) {
                int ny = now.y + dy[i];
                int nx = now.x + dx[i];
 
                if (ny < 0 || ny>200 || nx < 0 || nx>200) continue;
                if (visited[ny][nx][0]!=0) continue;
                visited[ny][nx][0] = 1;
                q.push({ ny, nx, 1, now.cnt+1 });
            }
        }
        else if (d == 1) {
            // 가로 이동
            for (int i = 2; i < 4; i++) {
                int ny = now.y + dy[i];
                int nx = now.x + dx[i];
 
                if (ny < 0 || ny>200 || nx < 0 || nx>200) continue;
                if (visited[ny][nx][1]!=0) continue;
                visited[ny][nx][1] = 1;
                q.push({ ny, nx, 0, now.cnt+1 });
            }
        }
    }
}
 
int main() {
 
    int t;
    cin >> t;
    for (int testcase = 0; testcase < t; testcase++) {
 
        cin >> sx >> sy >> ex >> ey;
        sx += 100;
        sy += 100;
        ex += 100;
        ey += 100;
        int res = bfs(sx, sy);
        cout << "#" << testcase+1<<" " <<res-1 << "\n";
    }
 
    return 0;
}
