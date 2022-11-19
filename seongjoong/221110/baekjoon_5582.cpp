#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;

string a;
string b;
int dp[4001][4001];
int ans;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> a >> b;

    for (int i = 1; i <= a.length(); i++) {
        for (int j = 1; j <= b.length(); j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > ans)
                    ans = dp[i][j];
            }
        }
    }

    cout << ans;

    return 0;
}
