#include <algorithm>
#include <cmath>
#include <limits.h>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

const int d4y[4] = {-1, 0, 1, 0};
const int d4x[4] = {0, -1, 0, 1};

int N, M;
vector<int> adjlist[1001];
bool visited[1001];

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
    cin >> N >> M;
    rep(i, M){
        int src, dest;
        cin >> src >> dest;
        adjlist[src].push_back(dest);
        adjlist[dest].push_back(src);
    }
}

void bfs(int start){
    queue<int> q;
    q.push(start);
    visited[start] = true;
    
    while(!q.empty()){
        int cur = q.front();
        q.pop();

        for(const auto& next: adjlist[cur]){
            if(visited[next]) continue;
            visited[next] = true;
            q.push(next);
        }
    }
}

void solve(){
    int cnt = 0;
    for(int n = 1; n <= N; n++){
        if(visited[n])
            continue;
        visited[n] = true;
        bfs(n);
        cnt++;
    }
    cout << cnt << '\n';
}