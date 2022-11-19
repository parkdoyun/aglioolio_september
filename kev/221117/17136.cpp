#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

int grid[10][10];
bool covered[10][10];
int used_paper[6];

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
    rep(i, 10){
        rep(j, 10){
            cin >> grid[i][j];
        }
    }
}

int get_possible_max_paper_size(int y, int x){
    int max_paper_size = 5;
    for(int k = max_paper_size; k > 0; k--){
        if(y + k > 10 || x + k > 10) continue;
        
        bool possible = true;
        for(int i = y; i < y + k; i++){
            for(int j = x; x < x + k; x++){
                possible &= grid[i][j] == 1;
            }
        }

        if(possible) break;
    }
    return max_paper_size;
}

void solve(){
    dfs()
}