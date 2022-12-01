// 2022-11-23 correct 30m / 12ms
#include <iostream>
#include <queue>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

typedef struct __node__{
    int y;
    int x;
}Node;

int N;
int grid[100][100];
bool visited[100][100];

void init();
void solve();

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int C; cin >> C;
    rep(i, C){
        init();
        solve();
    }
    return 0;
}

void init(){
    cin >> N;
    rep(i, N) rep(j, N) {
        cin >> grid[i][j];
        visited[i][j] = false;
    }
}

void solve(){    
    queue<Node> q;
    q.push({0, 0});
    visited[0][0] = true;
    while(!q.empty()){
        Node cur = q.front();
        q.pop();

        int stride = grid[cur.y][cur.x];
        
        int ny = cur.y;
        int nx = cur.x + stride;
        if(ny == N - 1 && nx == N - 1){
            cout << "YES" << "\n";
            return;
        }
        if(nx < N && !visited[ny][nx]){
            visited[ny][nx] = true;
            q.push({ny, nx});
        }
        
        ny = cur.y + stride; nx = cur.x;
        if(ny == N - 1 && nx == N - 1){
            cout << "YES" << "\n";
            return;
        }
        if(ny < N && !visited[ny][nx]){
            visited[ny][nx] = true;
            q.push({ny, nx});
        }
    }
    cout << "NO" << "\n";
}