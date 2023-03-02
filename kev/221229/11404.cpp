#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

#define all(v) (v).begin(), (v).end()

const int INF = INT_MAX / 2;

void solve(){
    int N; cin >> N;
    vector<vector<int>> distance(N + 1, vector<int>(N + 1, INF));
    
    int M; cin >> M;
    for (int i = 0; i < M; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        int& d = distance[a][b];
        d = min(d, c);
    }

    for(int k = 1; k < N + 1; ++k){
        for(int i = 1; i < N + 1; ++i){
            for(int j = 1; j < N + 1; ++j){
                if(i == j) continue;
                distance[i][j] = min(
                    distance[i][j],
                    distance[i][k] + distance[k][j]
                    );
            }
        }
    }

    for(int i = 1; i < N + 1; ++i){
        for(int j = 1; j < N + 1; ++j){
            int d = distance[i][j];
            if(d == INF) d = 0;
            cout << d << " ";
        }
        cout << "\n";
    }    
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}