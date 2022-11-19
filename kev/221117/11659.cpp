#include <iostream>
#include <vector>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)

void solve(){
    int N, M;
    cin >> N >> M;
    vector<int> v(N, 0);
    vector<pair<int, int>> queries(M);
    rep(i, N) cin >> v[i];
    rep(i, M) cin >> queries[i].first >> queries[i].second;
    
    vector<int> acc(N + 1, 0);
    for(int i = 1; i <= N; i++){
        acc[i] = acc[i - 1] + v[i - 1];
    }
    for(const auto& query: queries){
        int i = query.first;
        int j = query.second;
        cout << acc[j] - acc[i - 1] << '\n';
    }
}

int main(){
    solve();
    return 0;
}