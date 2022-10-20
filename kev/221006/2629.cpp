#include <iostream>
using namespace std;

bool dp[40001];
int w[30];
int m[7];

int N, M;

void dfs(int, int);

int main(){
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> w[i];
    }

    cin >> M;
    for(int i = 0; i < M; i++){
        cin >> m[i];
    }

    dfs(0, 0);

    for(int i = 0; i < M; i++){
        bool can_specify_weight = dp[m[i]];
        for(int j = 1; !can_specify_weight && j <= 40000 - m[i]; j++){
            if(!dp[j] || !dp[m[i] + j]) continue;
            can_specify_weight = true;
        }
        if(can_specify_weight) cout << "Y ";
        else cout << "N ";
    }
    cout << '\n';

    return 0;
}

void dfs(int idx, int weight){
    if(idx == N){
        dp[weight] = true;
        return;
    }

    if(dp[weight])
        return;
    
    for(int i = idx; i < N; i++){
        dfs(i + 1, weight + w[i]);
        dfs(i + 1, weight);
    }
}