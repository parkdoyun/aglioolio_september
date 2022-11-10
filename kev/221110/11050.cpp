#include <algorithm>
#include <cmath>
#include <limits.h>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

int N, K;
int binomial_coef[11][11];
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
    cin >> N >> K;
}

void solve(){
    binomial_coef[0][0] = 1;
    binomial_coef[1][0] = 1;
    binomial_coef[1][1] = 1;
    for(int n = 2; n <= N; n++){
        for(int k = 0; k <= n; k++){
            if(k == 0) binomial_coef[n][k] = 1;
            else binomial_coef[n][k] = binomial_coef[n - 1][k - 1] + binomial_coef[n - 1][k];
        }
    }
    cout << binomial_coef[N][K] << '\n';
}