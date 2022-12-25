#include <algorithm>
#include <cmath>
#include <limits.h>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

void init();
void solve();

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    init();
    solve();
    return 0;
}

int N, M;
vector<pair<int, int>> parent_child_relation;

int root;
vector<vector<int>> nodes;

void init(){
    cin >> N;
    parent_child_relation.resize(N);
    rep(i, N){
        int parent; cin >> parent;
        parent_child_relation[i] = {i, parent};
    }
    cin >> M;

    // 트리로 변환
    nodes.resize(N);
    for(const auto& r: parent_child_relation){
        int self = r.first;
        int parent = r.second;

        if(parent == -1){
            root = self;
            continue;
        }

        nodes[parent].push_back(self);
    }

}

int count_leaf_nodes(int idx){
    if(idx == M) return 0;
    if(nodes[idx].empty()) return 1;
    if(size(nodes[idx]) == 1 && nodes[idx][0] == M) return 1;

    int counter = 0;
    for(const auto& next: nodes[idx]){
        counter += count_leaf_nodes(next);
    }
    
    return counter;
}

void solve(){
    cout << count_leaf_nodes(root) << '\n';
}