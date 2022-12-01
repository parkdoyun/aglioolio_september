#include <iostream>
#include <limits.h>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)

int used_paper[5];
int grid[10][10];
int answer = INT_MAX;

int get_max_square_size(int i, int j){
    int size;
    for(size = 5; size > 1; size--){
        int h = i + size - 1, w = j + size - 1;
        if(h >= 10 || w >= 10) continue;

        bool valid = true;
        for(int y = i; y <= h; y++){
            for(int x = j; x <= w; x++){
                valid &= grid[y][x] == 1;
            }
        }

        if(valid) return size;
    }
    return size;
}

void put_paper(int i, int j, int size){
    int h = i + size - 1;
    int w = j + size - 1;
    for(int y = i; y <= h; y++){
        for(int x = j; x <= w; x++){
            grid[y][x] = 0;
        }
    }
}
void remove_paper(int i, int j, int size){
    int h = i + size - 1;
    int w = j + size - 1;
    for(int y = i; y <= h; y++){
        for(int x = j; x <= w; x++){
            grid[y][x] = 1;
        }
    }
}

void get_next_position(int i, int j, int& y, int& x){
    y = i, x = j;
    for(int n = i; n < 10; n++){
        for(int m = 0; m < 10; m++){
            if(grid[n][m] == 1){
                y = n; x = m;
                return;
            }
        }
    }
}

void dfs(int cnt, int i, int j){
    if(cnt >= answer)
        return;
    // 붙일 수 있는 가장 큰 색종이
    int max_square_size = get_max_square_size(i, j);
    
    for(int size = max_square_size; size > 0; size--){
        if(used_paper[size - 1] >= 5) continue;
        used_paper[size - 1]++;
        put_paper(i, j, size);
        
        int next_i, next_j;
        get_next_position(i, j, next_i, next_j);
        
        if(grid[next_i][next_j] == 0){
            answer = min(answer, cnt + 1);
        }
        else{
            dfs(cnt + 1, next_i, next_j);
        }

        remove_paper(i, j, size);
        used_paper[size - 1]--;
    }
}

void solve(){
    rep(i, 10) rep(j, 10) cin >> grid[i][j];

    int i, j;
    get_next_position(0, 0, i, j);
    if(grid[i][j] == 0) answer = 0;
    else dfs(0, i, j);

    if(answer == INT_MAX) cout << -1 << '\n';
    else cout << answer << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}