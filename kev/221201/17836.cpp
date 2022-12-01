#include <algorithm>
#include <cmath>
#include <limits.h>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())
#define INF INT_MAX

struct Node{
    int y;
    int x;
};

const int d4y[4] = {-1, 0, 1, 0};
const int d4x[4] = {0, -1, 0, 1};

int N, M, T;
Node S;
int grid[100][100];
int visited[100][100];

void init();
void solve();

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    init();
    solve();
    return 0;
}

void init(){
    cin >> N >> M >> T;
    Node sword;
    rep(i, N) rep(j, M){
        cin >> grid[i][j];
        if(grid[i][j] == 2){
            S = {i, j};
        }
        visited[i][j] = INF;
    }
}

void bfs(){
    queue<Node> q;
    q.push({0, 0});
    visited[0][0] = 0;
    while(!q.empty()){
        Node cur = q.front();
        q.pop();

        rep(k, 4){
            int ny = cur.y + d4y[k];
            int nx = cur.x + d4x[k];

            if(ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
            if(grid[ny][nx] == 1) continue;
            if(visited[ny][nx] != INF) continue;
            
            visited[ny][nx] = visited[cur.y][cur.x] + 1;
            q.push({ny, nx});
        }
    }
}

void solve(){
    bfs();

    if(visited[S.y][S.x] == INF  && visited[N - 1][M - 1] == INF) {
        cout << "Fail" << '\n';
        return;
    }

    Node d = {N - 1 - S.y, M - 1 - S.x};
    int faster = min(visited[N - 1][M - 1], visited[S.y][S.x] + d.y + d.x);
    
    if(faster <= T) cout << faster << "\n";
    else cout << "Fail" << "\n";  
}