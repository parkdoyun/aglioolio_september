#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <limits.h>
using namespace std;

// 조건을 만족하면서 최소비용
// N이 작음 -> DFS
// 00:29:49

#define rep(idx, n) for(int idx = 0; idx < (n); ++idx)
#define all(container) (container).begin(), (container).end()
#define size(container) (int)((container).size())

struct Ingredient{
    int p, f, s, v;
    int cost;
};

int N;
int P, F, S, V;
int min_cost = INT_MAX;
vector<int> min_cost_path;
vector<Ingredient> ingred;

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
    cin >> N;
    cin >> P >> F >> S >> V;
    vector<Ingredient> tmp_ingred(N);
    rep(i, N){
        cin >> tmp_ingred[i].p
            >> tmp_ingred[i].f
            >> tmp_ingred[i].s
            >> tmp_ingred[i].v
            >> tmp_ingred[i].cost;
    }
    swap(ingred, tmp_ingred);
}


void dfs(int idx, vector<int>& path, int p, int f, int s, int v, int cost){
    if(idx == N)
        return;

    if(cost >= min_cost)
        return;
    
    if(p >= P && f >= F && s >= S && v >= V){
        min_cost = cost;
        min_cost_path.clear();
        for(const auto& i: path){
            min_cost_path.push_back(i);
        }
        return;
    }

    for(int i = idx + 1; i < N; i++){
        path.push_back(i + 1);
        dfs(i, 
            path, 
            p + ingred[i].p,
            f + ingred[i].f, 
            s + ingred[i].s,
            v + ingred[i].v,
            cost + ingred[i].cost
            );
        path.pop_back();
    }
}

void solve(){
    for(int i = 0; i < N; i++){
        vector<int> path;
        path.push_back(i + 1);
        dfs(i,
            path,
            ingred[i].p,
            ingred[i].f,
            ingred[i].s,
            ingred[i].v,
            ingred[i].cost
            );
        path.pop_back();
    }
    
    if(min_cost == INT_MAX){
        cout << -1 << '\n';
        return;
    }

    cout << min_cost << '\n';
    for(const auto& i: min_cost_path)
        cout << i << " ";
    cout << '\n';
}