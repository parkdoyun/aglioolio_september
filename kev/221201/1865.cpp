#include <iostream>
#include <vector>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

// N개 지점, M개의 도로, W개의 웜홀
// 도로 방향 x, 웜홀 방향 o
struct Node{
    int e;
    int t;
}

int N, M, W;
void solve(){
    cin >> N >> M >> W;
    vector<Node> roads(N + 1);
    rep(i, M) {
        int s; cin >> s;
        int e; cin >> e;
        int t; cin >> t;
        roads[s].push_back({e, t});
        roads[e].push_back({s, t});
    }
    vector<Node> wormholes(N + 1);
    rep(i, W){
        int s; cin >> s;
        int e; cin >> e;
        int t; cin >> t;
        wormholes[s].push_back({e, t});
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T; cin >> T;
    rep(t, T) solve();

    return 0;
}