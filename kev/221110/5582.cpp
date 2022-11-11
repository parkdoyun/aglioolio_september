#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define size(v) (int)((v).size())

int dp[4001][4001];
void solve();

// dp
/* 
현재 비교한 좌표가 (i, j)일 때,
(i - 1, j - 1)은 직전 문자까지 이어진 공통 문자열의 길이가 된다.
  a b r a c a d a b r a
e 0 0 0 0 0 0 0 0 0 0 0
c 0 0 0 0 1 0 0 0 0 0 0  
a 1 0 0 1 0 2 0 1 0 0 1
...
*/
int main(){
    solve();
    return 0;
}

void solve(){
    string a; cin >> a;
    string b; cin >> b;
    int lcs_length = 0; // longest common string

    for(int i = 0; i < size(a); i++){
        for(int j = 0; j < size(b); j++){
            if(a[i] == b[j]){
                dp[i + 1][j + 1] = dp[i][j] + 1;
            }
            else{
                dp[i + 1][j + 1] = 0;
            }
            lcs_length = max(lcs_length, dp[i + 1][j + 1]);
        }
    }
    cout << lcs_length << '\n';
}