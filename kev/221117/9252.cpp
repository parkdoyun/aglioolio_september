#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

void solve(){
    string a; cin >> a;
    string b; cin >> b;

    vector<vector<int>> dp(size(a) + 1, vector<int>(size(b) + 1, 0));
    for(int i = 0; i < size(a); i++){
        for(int j = 0; j < size(b); j++){
            if(a[i] == b[j]){
                dp[i + 1][j + 1] = dp[i][j] + 1;
            }
            else{
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
    }

    int len_lcs = dp[size(a)][size(b)];
    cout << len_lcs << '\n';
    
    if(len_lcs > 0){
        int i = size(a), j = size(b);
        int cnt = 0;
        string lcs;
        while(cnt < len_lcs){
            if(a[i - 1] == b[j - 1]){
                cnt++; lcs.push_back(a[i - 1]);
                i--; j--;
                continue;
            }
            
            if(dp[i][j] == dp[i - 1][j]){
                i--;
                continue;
            }

            if(dp[i][j] == dp[i][j - 1]){
                j--;
                continue;
            }
        }
        reverse(all(lcs));
        cout << lcs << '\n';
    }
}

int main(){
    solve();
    return 0;
}