#include <iostream>
#include <queue>
using namespace std;
 
struct Pos {
    int y;
    int x;
};
 
int n;
Pos Start;
Pos End;
int MAP[16][16];
int visited[16][16];
 
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int bfs(int y, int x) {
 
    queue<Pos> q;
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = 2134567890;
        }
    }
 
    q.push({ y, x });
    visited[y][x] = 0;
 
    while (!q.empty()) {
        Pos now = q.front();
        q.pop();
 
        for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];
 
            if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
            if (MAP[ny][nx] == 1) continue;
 
            int nextTime = visited[now.y][now.x];
            if (MAP[ny][nx] == 2) {
                if (nextTime % 3 == 0) {
                    nextTime += 3;
                }
                else if (nextTime % 3 == 1) {
                    nextTime += 2;
                }
                else if(nextTime % 3 == 2){
                    nextTime+=1;
                }
                 
                if (visited[ny][nx] <= nextTime) continue;
                visited[ny][nx] = nextTime;
                q.push({ ny, nx });
            }
 
            else {
                if (visited[ny][nx] <= visited[now.y][now.x]+1) continue;
                visited[ny][nx] = visited[now.y][now.x]+1;
                q.push({ ny, nx });
            }
        }
    }
 
    return visited[End.y][End.x];
 
}
 
int main() {
 
    int t;
    cin >> t;
 
    for (int testcase = 0; testcase < t; testcase++) {
 
        cin >> n;
 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> MAP[i][j];
            }
        }
 
        cin >> Start.y >> Start.x;
        cin >> End.y >> End.x;
 
        int res = bfs(Start.y, Start.x);
 
        if (res == 2134567890) {
            cout << "#" << testcase + 1 << " " << -1 << "\n";
        }
        else {
            cout << "#" << testcase + 1 << " " << res << "\n";
        }
    }
 
    return 0;
}
                 
