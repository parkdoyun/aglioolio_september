#include <algorithm>
#include <cmath>
#include <limits.h>
#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

void init();
void solve();

int N;
int triangle[100][100];
int cache[100][100];

int main(){
    ios_base::sync_with_stdio(0);
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
    for(int i = 0; i < N; i++){
        for(int j = 0; j <= i; j++){
            cin >> triangle[i][j];
        }
    }
    memset(cache, -1, sizeof(cache));
}

int move(int i, int j){
    int& ret = cache[i][j];
    if(i == N - 1)
        return ret = triangle[i][j];
    
    if(ret != -1)
        return ret;

    return ret = max(
        move(i + 1, j),
        move(i + 1, j + 1)
    ) + triangle[i][j];
}

void solve(){
    int answer = move(0, 0);
    cout << answer << "\n";
}