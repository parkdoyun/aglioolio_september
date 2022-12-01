#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

int N;
int A[8];
int B[8];
bool used[8];
int answer = INT_MIN;

int calculate(){
    int result = 0;
    for(int i = 1; i < N; i++){
        result += abs(B[i] - B[i - 1]);
    }
    return result;
}

void dfs(int idx){
    if(idx == N){
        answer = max(answer, calculate());
        return;
    }

    for(int i = 0; i < N; i++){
        if(used[i]) continue;
        used[i] = true;
        B[idx] = A[i];
        dfs(idx + 1);
        used[i] = false;
    }
}

void solve(){
    cin >> N;
    rep(i, N) cin >> A[i];
    dfs(0);
    cout << answer << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;    
}