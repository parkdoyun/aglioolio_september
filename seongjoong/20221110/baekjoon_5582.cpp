#include <iostream>
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

============================================================

// DP 테이블 전부 채우는 풀이 방법

#include <iostream>
using namespace std;

string a;
string b;
int dp[4001][4001];
int flag[4001][4001]; // 같은 글자인 경우 기록

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> a >> b;

    for (int i = 1; i <= a.length(); i++) {
        for (int j = 1; j <= b.length(); j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (a[i - 1] == b[j - 1]) {
                flag[i][j] = flag[i - 1][j - 1] + 1;
                dp[i][j] = max(dp[i][j], flag[i][j]);
            }
        }
    }

    cout << dp[a.length()][b.length()];

    return 0;
}
