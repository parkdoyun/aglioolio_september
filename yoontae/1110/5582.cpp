#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string s1, s2;
int dp[4001][4001];

void input() {
	cin >> s1 >> s2;
}

void solve() {
	int len1 = (int)(s1.length());
	int len2 = (int)(s2.length());

	for (int i = 0; i < len1; i++) {
		for (int j = 0; j < len2; j++) {
			if (s1[i] != s2[j])
				continue;

			if (i - 1 < 0 || j - 1 < 0) {
				dp[i][j] = 1;
			}
			else {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
		}
	}

	int ans = 0;

	for (int i = 0; i < len1; i++) {
		for (int j = 0; j < len2; j++) {
			ans = max(ans, dp[i][j]);
		}
	}

	cout << ans;
}

int main() {
	input();
	solve();

	return 0;
}