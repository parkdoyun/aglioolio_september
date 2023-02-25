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

struct Edge{
    int src, dest;
};

int N, M;

vector<int> ancestor;
vector<int> depth;
vector<Edge> edges;

void init(){
    cin >> N >> M;
    
    ancestor.resize(N); for(int i = 0; i < N; ++i) ancestor[i] = i;
    depth.resize(N); for(int i = 0; i < N; ++i) depth[i] = 1;
    
    edges.resize(M);
    rep(i, M){
        cin >> edges[i].src >> edges[i].dest;
    }
}

int find_ancestor(int n){
    if(ancestor[n] == n) return n;
    else return ancestor[n] = find_ancestor(ancestor[n]);
}

bool merge(int n, int m){
    int an = find_ancestor(n); // ancestor of n
    int am = find_ancestor(m); // ancestor of m

    if(an == am) return false; // 사이클 발견

    if(depth[an] < depth[am]) ancestor[an] = am;
    else ancestor[am] = an;

    if(depth[an] == depth[am]) depth[an]++;

    return true;
}

void solve(){
    for(int i = 0; i < M; ++i){
        if(!merge(edges[i].src, edges[i].dest)){
            cout << i + 1 << "\n";
            return;
        }
    }
    cout << 0 << "\n";
}