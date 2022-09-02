#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

typedef struct _edge{
    int src;
    int dest;
    int cost;
}Edge;

vector<Edge> roads;

int ancestor[100001];
int depth[100001];

int get_ancestor(int n){
    if(ancestor[n] == n)
        return n;
    else
        return ancestor[n] = get_ancestor(ancestor[n]);
}

bool merge(int n, int m){
    int an = get_ancestor(n);
    int am = get_ancestor(m);

    if(an == am)
        return false;
    
    if(depth[am] > depth[an])
        ancestor[an] = am;
    else
        ancestor[am] = an;
    
    if(depth[an] == depth[am])
        depth[an]++;

    return true;
}

int main(){
    int N; cin >> N; // 집의 개수
    int M; cin >> M; // 길의 개수
    for(int i = 0; i < M; i++){
        int src; cin >> src;
        int dest; cin >> dest;
        int cost; cin >> cost;
        roads.push_back({src, dest, cost});
    }

    sort(roads.begin(), roads.end(), [](const Edge& l, const Edge& r){
        return l.cost < r.cost;
    });

    for(int i = 1; i <= N; i++) 
        ancestor[i] = i;
    
    int min_cost = 0; // 모든 마을을 연결하는데 드는 가장 적은 비용 -> MST cost
    int max_road_cost = INT_MIN; // MST 구성하는 간선 중 가장 비싼 길
    
    // MST 만드는 루프
    for(const Edge& e: roads){    
        if(!merge(e.src, e.dest))
            continue;

        min_cost += e.cost;
        max_road_cost = e.cost;
    }

    int answer = min_cost - max_road_cost;

    cout << answer << '\n';
}