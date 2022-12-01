#include <iostream>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

int cache[101][101];

int bino(int n, int r){
    if(r == 0 || n == r) return 1;
    if(cache[n][r] != -1) return cache[n][r];
    return cache[n][r] = bino(n - 1, r - 1) + bino(n - 1, r);
}

int main(){
    rep(i, 101) rep(j, 101) cache[i][j] = -1;

    cout << bino(81, 23) << "\n";

    return 0;
}