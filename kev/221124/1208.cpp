#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())
#define ll long long

// brute forcing 시간 초과
// dp

void solve();

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}

int N, S;
vector<int> seq;
int answer = 0;

void solve(){
    cin >> N >> S;
    seq.resize(N);
    rep(i, N) cin >> seq[i];
    
    for(ll k = 1; k < (ll)pow(2, N); k++){
        int sum = 0;
        for(int i = 0; i < size(seq); i++){
            ll bit = 1 << i;
            if(k & bit) sum += seq[i];
        }
        if(sum == S) answer++;
    }
    
    cout << answer << '\n';
}