#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <limits.h>
using namespace std;

#define rep(idx, n) for(int idx = 0; idx < (n); ++idx)
#define all(container) (container).begin(), (container).end()
#define size(container) (int)((container).size())

int N;
bool adjmatrix[11][11];
int p[11];
int answer = INT_MAX;

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
    for(int i = 1; i <= N; i++)
        cin >> p[i];
    
    for(int i = 1; i <= N; i++){
        int M; cin >> M;
        rep(j, M){
            int k; cin >> k;
            adjmatrix[i][k] = true;
        }
    }
}

int bfs(const vector<int>& s){
    bool element_of_set[11] = {false, };
    for(const auto& a: s)
        element_of_set[a] = true;
    
    bool visited[11] = {false, };
    int start = s[0];
    visited[start] = true;
    int cnt = 1;
    
    queue<int> q;
    q.push(start);
    while(!q.empty()){
        int cur = q.front();
        q.pop();

        for(int i = 1; i <= N; i++){
            if(!adjmatrix[cur][i]) continue;
            if(!element_of_set[i]) continue;
            if(visited[i]) continue;
            
            visited[i] = true;
            cnt++;
            
            q.push(i);
        }
    }

    return cnt;
}

bool is_sector_valid(const vector<int>& s){
    int connected_areas = bfs(s);
    bool is_valid = connected_areas == size(s);
    return is_valid;
}

void dfs(int idx, vector<int>& s){
    if(idx == N){
        if(size(s) == 0 || size(s) == N)
            return;
        
        vector<bool> taken(N + 1, false);
        for(const auto& a: s) taken[a] = true;

        vector<int> t;
        for(int i = 1; i <= N; i++){
            if(taken[i]) continue;
            t.push_back(i);
        }

        if(!is_sector_valid(s) || !is_sector_valid(t))
            return;
        
        int diff = 0;
        for(int i = 1; i <= N; i++){
            if(taken[i]) diff += p[i];
            else diff -= p[i];
        }

        answer = min(answer, abs(diff));
        return;
    }

    for(int i = idx + 1; i <= N; i++){
        s.push_back(i);
        dfs(i, s);
        s.pop_back();
        dfs(i, s);
    }
}

void solve(){
    // 두 선거구로 나누는 모든 경우의 수
    vector<int> sector;
    for(int i = 1; i <= N; i++){
        sector.push_back(i);
        dfs(i, sector);
        sector.pop_back();
    }

    if(answer == INT_MAX) cout << -1 << '\n';
    else cout << answer << '\n';
}