#include <algorithm>
#include <array>
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

struct Coord{
    int x, y, z;
};

struct Planet{
    int id;
    Coord pos;
};

struct Subtree{
    int root;
    int height;
};

struct Edge{
    int src, dest;
    int cost;
};

bool operator < (const Edge& l, const Edge& r){
    return l.cost < r.cost;
}

int N;
vector<Planet> planets;
vector<Subtree> subtrees;
vector<Edge> edges;

void init(){
    cin >> N;
    
    planets.resize(N);
    subtrees.resize(N);
    
    rep(i, N){
        planets[i].id = i;
        Coord& pos = planets[i].pos;
        cin >> pos.x >> pos.y >> pos.z;
        subtrees[i] = {i, 1};
    }
}

int get_root(int n){
    if(subtrees[n].root == n) return n;

    return subtrees[n].root = get_root(subtrees[n].root);
}

void connect_subtrees(Subtree& g, Subtree& h){
    if(g.height < h.height) {g.root = h.root;}
    else if(g.height > h.height) {h.root = g.root;}
    else {h.root = g.root; g.height++;}
}

int get_ternal_cost(const Coord& a, const Coord& b){
    array<int, 3> d;
    
    d[0] = abs(a.x - b.x);
    d[1] = abs(a.y - b.y);
    d[2] = abs(a.z - b.z);

    return *min_element(all(d));
}

bool by_x(const Planet& l, const Planet& r){
    return l.pos.x < r.pos.x;
}

bool by_y(const Planet& l, const Planet& r){
    return l.pos.y < r.pos.y;
}

bool by_z(const Planet& l, const Planet& r){
    return l.pos.z < r.pos.z;
}

void solve(){
    
    sort(all(planets), by_x);
    for(int i = 1; i < N; ++i){
        const Planet& a = planets[i - 1];
        const Planet& b = planets[i];
        edges.push_back({a.id, b.id, get_ternal_cost(a.pos, b.pos)});
    }

    sort(all(planets), by_y);
    for(int i = 1; i < N; ++i){
        const Planet& a = planets[i - 1];
        const Planet& b = planets[i];
        edges.push_back({a.id, b.id, get_ternal_cost(a.pos, b.pos)});
    }

    sort(all(planets), by_z);
    for(int i = 1; i < N; ++i){
        const Planet& a = planets[i - 1];
        const Planet& b = planets[i];
        edges.push_back({a.id, b.id, get_ternal_cost(a.pos, b.pos)});
    }

    sort(all(edges));

    int total_cost = 0;
    int ternal_counter = 0;
    for(const auto& edge: edges){
        int src = edge.src;
        int dest = edge.dest;
        int cost = edge.cost;

        Subtree& g = subtrees[get_root(src)];
        Subtree& h = subtrees[get_root(dest)];
        
        if(g.root == h.root) continue;
        connect_subtrees(g, h);
        total_cost += cost;
        
        ternal_counter++;
        if(ternal_counter == N - 1) break;
    }

    cout << total_cost << "\n";
}