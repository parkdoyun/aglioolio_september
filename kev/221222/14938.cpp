#include <algorithm>
#include <cmath>
#include <limits.h>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <array>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

const int d4y[4] = {-1, 0, 1, 0};
const int d4x[4] = {0, -1, 0, 1};

void init();
void solve();

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    init();
    solve();
    return 0;
}

struct Edge{
    int dest;
    int cost;
};

int N, M, R;
vector<int> num_items;
vector<vector<int>> distance_vector;

void init(){
    cin >> N >> M >> R;
    
    num_items.resize(N + 1);
    rep(i, N) cin >> num_items[i + 1];

    distance_vector.resize(N + 1);
    for(auto& row: distance_vector) row.resize(N + 1);

    rep(i,  N + 1) rep(j, N + 1) {
        if(i == j) distance_vector[i][j] = 0;
        else distance_vector[i][j] = INT_MAX;
    }

    rep(i, R){
        int src; cin >> src;
        int dest; cin >> dest;
        int cost; cin >> cost;

        distance_vector[src][dest] = cost;
        distance_vector[dest][src] = cost;
    }

}

void solve(){
    // 시작 노드에서 다른 모든 노드까지의 거리 구하기
    // 다른 노드까지의 거리가 수색 범위 내일 경우 해당 노드에 놓여져 있는 아이템을 모두 획득
    vector<vector<int>>& dv = distance_vector;
    
    for(int k = 1; k <= N; ++k){
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= N; ++j){
                if(dv[i][k] == INT_MAX || dv[k][j] == INT_MAX) continue;
                dv[i][j] = min(dv[i][j],dv[i][k] + dv[k][j]);
            }
        }
    }

    int max_item_gain = -1;

    for(int landing_area = 1; landing_area <= N; ++landing_area){
        int item_gain = 0;
        for(int ohter_area = 1; ohter_area <= N; ++ohter_area){
            if(dv[landing_area][ohter_area] > M) continue;
            item_gain += num_items[ohter_area];
        }
        max_item_gain = max(max_item_gain, item_gain);
    }
    cout << max_item_gain << '\n';
}