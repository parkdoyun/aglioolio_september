#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

// dfs, dp, bitmasking 혼합 문제
// 재귀를 이해할 수 없다..

const int INF = 16e6 + 1;
int N;
int g[16][16];
int dp[16][1 << 16];

int tsp(int cur, int visited){
    if(visited == (1 << N) - 1){
        if(g[cur][0] != 0)
            return g[cur][0];
        else
            return INF;
    }

    if(dp[cur][visited] != 0) return dp[cur][visited];
    dp[cur][visited] = INF;
    
    for (int i = 0; i < N; i++)
    {
        if(g[cur][i] == 0) continue;
        if(visited & (1 << i)) continue;
        dp[cur][visited] = min(
                                dp[cur][visited], 
                                tsp(i, visited | (1 << i)) + g[cur][i]
                            );
    }
    return dp[cur][visited];
}

void solve(){
    cin >> N;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cin >> g[i][j];

    int answer = tsp(0, 1);
    cout << answer << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}