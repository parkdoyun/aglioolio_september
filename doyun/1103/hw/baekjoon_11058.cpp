#include <iostream>
#include <algorithm>

using namespace std;

// 백준 11058 - 크리보드
// DP
// 골드 5

// 항상 ctrl-A + ctrl-V를 한번에 하도록 하자 
// 1) A 출력(DP[i-1] + 1)이 더 큰지
// 2) 바로 ctrl-A + ctrl-C + ctrl-V를 한 게 더 큰지(DP[i-3] + DP[i-3])
// 3) ctrl-A + ctrl-C + ctrl-V + ctrl-V (DP[i-4] + DP[i-4] + DP[i-4])
// 4) ctrl-A + ctrl-C + ctrl-V + ctrl-V + ctrl-V (DP[i-5] * 4)
// 그 4번째 ctrl-V보다 다시 ctrl-A + ctrl-C + ctrl-V를 하는 게 더 크다


long long DP[101];

int main()
{
	int n;
	cin >> n;

	// 기저 조건
	// 그냥 A 누를때가 최대임
	// DP[0] = 0;
	DP[1] = 1;
	DP[2] = 2;


	for (int i = 3; i <= n; i++)
	{
		DP[i] = DP[i - 1] + 1;
		DP[i] = max(DP[i], DP[i - 3] * 2);
		DP[i] = max(DP[i], DP[i - 4] * 3);
		DP[i] = max(DP[i], DP[i - 5] * 4);
	}

	cout << DP[n];

	return 0;
}