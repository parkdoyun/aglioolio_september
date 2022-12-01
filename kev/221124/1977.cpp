#include <iostream>
#include <limits.h>
using namespace std;


// 7m 08s, 0ms

void solve(){
    bool is_square[10001] = {false,};
    for(int n = 1; n <= 100; n++) is_square[n*n] = true;
    
    int M, N;
    cin >> M >> N;
    int sum = 0;
    int min = INT_MAX;
    for(int i = M; i <= N; i++){
        if(is_square[i]) {
            min = i < min ? i : min;
            sum += i;
        }
    }
    
    if(sum == 0) cout << -1 << "\n";
    else cout << sum << "\n" << min << "\n";
}

int main(){
    solve();
    return 0;
}