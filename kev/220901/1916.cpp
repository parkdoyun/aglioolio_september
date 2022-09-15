#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

typedef struct _edge{
    int dest;
    int cost;
}Edge;

typedef struct _node{
    int city;
    int acc_cost;
}Node;

int cost[1001];

bool operator < (const Node& l, const Node& r){
    return l.acc_cost > r.acc_cost;
}

int N, M;
int start_city, end_city;

vector<Edge> v[100001];

void init(){
    cin >> N;
    cin >> M;
    for(int i = 0; i < M; i++){
        int src; cin >> src;
        int dest; cin >> dest;
        int cost; cin >> cost;
        v[src].push_back({dest, cost});
    }
    cin >> start_city >> end_city;

    for(int i = 0; i <= N; i++)
        cost[i] = INT_MAX;
}

int dijkstra(){
    priority_queue<Node> pq;
    pq.push({start_city, 0});
    cost[start_city] = 0; // 시작 도시, 누적 비용

    while(!pq.empty()){
        Node cur = pq.top();
        pq.pop();
        
        int city = cur.city;
        int acc_cost = cur.acc_cost;

        if(acc_cost > cost[city])
            continue;
        
        // 비용이 가장 적게 드는 경로 순으로 q에 넣는다
        for(const Edge& e: v[city]){
            int next = e.dest;
            int next_cost = cost[city] + e.cost;

            if(next_cost >= cost[next])
                continue;

            cost[next] = next_cost;

            pq.push({next, next_cost});
        }
    }
    return cost[end_city];
}

void solve(){
    int answer = dijkstra();
    cout << answer << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    init();
    solve();

    return 0;
}