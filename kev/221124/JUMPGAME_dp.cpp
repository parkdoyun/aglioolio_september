// 2022-11-23 correct 30m / 12ms
#include <iostream>
#include <queue>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

int N;
int grid[100][100];
int reached[100][100];

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
        reached[i][j] = -1;
    }
}

int jump(int y, int x){
    if(y >= N || x >= N) return 0;
    if(y == N - 1 && x == N - 1) return 1;
    
    int& ret = reached[y][x];
    if(ret != -1) return ret;
    
    int stride = grid[y][x];
    return ret = jump(y + stride, x) || jump(y, x + stride);
}

void solve(){    
    if(jump(0, 0) == 1) cout << "YES" << "\n";
    else cout << "NO" << "\n";
}