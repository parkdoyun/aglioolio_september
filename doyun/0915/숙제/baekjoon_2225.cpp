#include <iostream>
#include <string>
#include <stack>

using namespace std;

// 백준 2225 - 합분해
// DP
// 골드 5

// 점화식 : N을 K개의 숫자로 만드는 경우의 수 = 0부터 N까지 k-1개의 숫자로 만드는 경우의 수들의 총 합
// 어차피 기존의 가짓수(K-1개로 만드는 것)에 숫자 한개만 더하면 되므로 (0~N, 더하는 숫자 한개는 무조건 *하나*로 정해져 있다)
// DP[K][N] = DP[K-1][0] + DP[K-1][1] + ... + DP[K-1][N]
// 기저조건 1) K=1개로 만드는 N은 한가지이다 -> DP[1][N] = 1;
//          2) K개로 만드는 N=0은 한가지이다(0 + 0 + .. + 0) -> DP[K][0] = 1;  

long long DP[201][201];

int main()
{
	int n, k;
	cin >> n >> k;

	for (int i = 0; i <= n; i++)
	{
		DP[1][i] = 1;
	}

	for (int i = 0; i <= k; i++)
	{
		DP[i][0] = 1;
	}

	// DP
	// 수가 매우 커질 수 있으므로 1000000000보다 커질 때마다 나머지 연산해준다
	// 어차피 나머지 출력하므로 중간에 나머지 계산해줘도 상관 없다
	for (int i = 1; i <= k; i++)
	{
		DP[i][0] = DP[i - 1][0];
		for (int j = 1; j <= n; j++)
		{
			if (DP[i][j - 1] + DP[i - 1][j] > 1000000000)
			{
				DP[i][j] = (DP[i][j - 1] + DP[i - 1][j]) % 1000000000;
			}
			else DP[i][j] = DP[i][j - 1] + DP[i - 1][j];
		}
		
	}

	cout << DP[k][n] % 1000000000;

	return 0;
}