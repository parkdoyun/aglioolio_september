#include <iostream>

using namespace std;

// 백준 9084 - 동전
// DP
// 골드 5

// 그 전까지의 가짓수에 현재 가짓수 더한다
// 현재 동전이 가장 크므로 기존의 가짓수와 다른 새로운 가짓수이다
// 점화식 : DP[i][j] = DP[i-1][j] + DP[i][j - coin[i]]; 

int coin[21];
int DP[21][10001];

int main()
{
	int T, n, m;
	cin >> T;
	for (int tc = 0; tc < T; tc++)
	{
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> coin[i];
		}

		cin >> m;


		// 0번째 먼저 (기저 조건)
		for (int j = coin[0]; j <= m; j+=coin[0])
		{
			DP[0][j] = 1;
		}

		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j <= m; j++)
			{
				if (j < coin[i]) DP[i][j] = DP[i - 1][j];
				else if (j == coin[i]) DP[i][j] = DP[i - 1][j] + 1; // 현재 동전 1개로만 이루어진 경우
				else DP[i][j] = DP[i - 1][j] + DP[i][j - coin[i]];
			}
		}
		cout << DP[n - 1][m] << '\n';

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j <= m; j++) // 범위 주의
			{
				DP[i][j] = 0;
			}
		}
	}
	return 0;
}