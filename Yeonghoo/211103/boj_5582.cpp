/* Category : DP
*  solving time : 30 min
* /

#include <iostream>
#define INF 2123456789
using namespace std;

int dp[4000][4000];
string str1;
string str2;


void init() {
	dp[4000][4000] = { 0, };
	str1 = "";
	str2 = "";
}

void input() {
	cin >> str1 >> str2;
}

int main() {
	init();
	input();

	int answer = -INF;
	for (int i = 0; i < str1.size(); i++) {
		for (int j = 0; j < str2.size(); j++) {
			if (str1[i] == str2[j]) {
				if (i == 0 || j == 0) {
					dp[i][j] = 1;
				}
				else {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
			}
			else {
				dp[i][j] = 0;
			}
			if (dp[i][j] > answer) {
				answer = dp[i][j];
			}
		}
	}

	cout << answer;
}
