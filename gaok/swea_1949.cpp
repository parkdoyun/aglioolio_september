#include <iostream>
#include <vector>
using namespace std;
 
int n, k;
int maxHeight=-2134567890;
int MAP[9][9];
 
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int visited[9][9];
int maxLen = 0;
int flag = 0;
 
void dfs(int row, int col, int len) {
 
    if (maxLen < len) maxLen = len;
 
    for (int i = 0; i < 4; i++) {
        int ny = row + dy[i];
        int nx = col + dx[i];
 
        if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
        if (visited[ny][nx] != 0) continue;
        if (MAP[ny][nx] >= MAP[row][col]) {
            // 깊이 깎기 
            if (flag == 1) continue;
            for (int j = 0; j <= k; j++) {
                if (flag == 0) {
                    int height = MAP[ny][nx];
                    if (height - j < MAP[row][col]) {
                        MAP[ny][nx] -= j;
                        flag = 1;
                        visited[ny][nx] = 1;
                        dfs(ny, nx, len + 1);
                        visited[ny][nx] = 0;
                        MAP[ny][nx] = height;
                        flag = 0;
                    }
 
                }
            }
             
        }
 
        else {
            visited[ny][nx] = 1;
            dfs(ny, nx, len + 1);
            visited[ny][nx] = 0;
        }
    }
 
}
 
void init() {
    maxHeight = -2134567890;
    maxLen = 0;
    flag = 0;
}
 
int main() {
 
    int t;
    cin >> t;
 
    for (int testcase = 0; testcase < t; testcase++) {
         
        cin >> n >> k;
 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> MAP[i][j];
                if (MAP[i][j] > maxHeight) maxHeight = MAP[i][j];
            }
        }
 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (MAP[i][j] == maxHeight) {
                    // dfs
                    visited[i][j] = 1;
                    dfs(i, j, 1);
                    visited[i][j] = 0;
                }
            }
        }
 
        cout << "#"<<testcase+1<<" "<<maxLen << "\n";
 
        init();
    }
 
    return 0;
}
