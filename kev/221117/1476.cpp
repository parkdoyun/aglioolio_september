#include <iostream>
using namespace std;

void solve();

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}

void solve(){
    // E[1, 15] S[1, 28] M[1, 19]
    int E, S, M;
    cin >> E >> S >> M;
    int e, s, m;
    int cnt = 0;
    e = s = m = 0;
    while(e != E || s != S || m != M){
        e = cnt % 15 + 1;
        s = cnt % 28 + 1;
        m = cnt % 19 + 1;
        cnt++;
    }
    cout << cnt << '\n';
}