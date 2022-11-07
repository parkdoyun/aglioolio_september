#include <iostream>
#include <string>

using namespace std;

int DP[4002][4002];

// 백준 5582 - 공통 부분 문자열
// DP, LCS(Longest Common String)

int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	int max = 0;
	for (int i = 1; i <= s1.size(); i++)
	{
		for (int j = 1; j <= s2.size(); j++)
		{
			if (s1[i - 1] == s2[j - 1]) {
				DP[i][j] = DP[i - 1][j - 1] + 1;
				if (DP[i][j] > max) max = DP[i][j];
			}
		}
	}
	cout << max;


	return 0;
}