#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>
using namespace std;

#define rep(idx, n) for(int idx = 0; idx < (n); ++idx)
#define all(container) (container).begin(), (container).end()
#define size(container) (int)((container).size())
#define pii pair<int, int>

int N, M;
int A, B;
vector<vector<pii>> g;
vector<int> capacity;
struct Node{
    int src;
    int dest;
    int cost;
};

bool operator < (const Node& l, const Node& r) { 
    return l.cost < r.cost; 
}


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
    vector<vector<pii>> tmp_g(N + 1);
    vector<int> tmp_capacity(N + 1, 0);
    rep(i, M){
        int src; cin >> src;
        int dest; cin >> dest;
        int cost; cin >> cost;
        tmp_g[src].push_back({dest, cost});
        tmp_g[dest].push_back({src, cost});
    }
    cin >> A >> B;

    swap(g, tmp_g);
    swap(capacity, tmp_capacity);
}

void dijkstra(int src){
    capacity[src] = INT_MAX;
    priority_queue<Node> pq; 
    for(const auto& p: g[src]) pq.push({src, p.first, p.second});
    while(!pq.empty()){
        auto cur = pq.top();
        pq.pop();

        int from = cur.src;
        int to = cur.dest;
        int cost = cur.cost;

        int cap = min(capacity[from], cost);
        if(capacity[to] >= cap)
            continue;
        capacity[to] = cap;
        
        for(const auto& p: g[to]){
            int next = p.first;
            int next_cost = p.second;
            int next_cap = min(capacity[to], next_cost);
            if(capacity[next] >= next_cap)
                continue;
            pq.push({to, next, next_cost});
        }
    }
}

void solve(){
    dijkstra(A);
    cout << capacity[B] << '\n';
}