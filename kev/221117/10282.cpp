#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

// 2022-11-11 13:03 ~ 14:08

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())
#define pii pair<int, int>

struct Node{
    int id;
    int time_infected;
};

bool operator < (const Node& l, const Node& r){
    return r.time_infected < l.time_infected;
}

void init();
void solve();

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int T; cin >> T;
    rep(t, T){
        init();
        solve();
    }

    return 0;
}

// 몇 대의 컴퓨터가 감염되며, 걸리는 시간?
// dijkstra

int N, D, C;

vector<vector<pii>> graph;
vector<int> infection_record;

void init(){
    cin >> N >> D >> C;

    graph.clear();
    graph.resize(N + 1);

    infection_record.clear();
    infection_record.resize(N + 1);
    rep(i, N + 1) infection_record[i] = INT_MAX;
    
    int a, b, s;
    rep(i, D){
        cin >> a >> b >> s;
        graph[b].push_back({a, s});
    }
}

void dijkstra(int root){
    priority_queue<Node> pq;
    pq.push({root, 0});
    
    while(!pq.empty()){
        Node node = pq.top();
        pq.pop();
        
        int cur = node.id;
        int time_infected = node.time_infected;

        if(time_infected > infection_record[cur])
            continue;
        infection_record[cur] = time_infected;

        for(const auto& node: graph[cur]){
            int next = node.first;
            int delay = node.second;
            int time_after_propagation = time_infected + delay;

            if(time_after_propagation >= infection_record[next])
                continue;

            pq.push({next, time_after_propagation});
        }
    }
}

void print(const pair<int, int>& p){
    cout << p.first << " " << p.second << '\n';
}

void solve(){
    dijkstra(C);

    int count = 0;
    int time_elapsed = 0;
    for(int i = 1; i <= N; i++){
        if(infection_record[i] == INT_MAX)
            continue;
        count++;
        time_elapsed = max(time_elapsed, infection_record[i]);
    }
    cout << count << " " << time_elapsed << '\n';
}