#include <iostream>
#include <algorithm>

using namespace std;

// 백준 2616 - 소형기관차
// DP
// 골드 3

// 바로 전꺼가 더 많은지 vs 바로 이전 객차랑 합친 거가 더 많은지
// DP[0] : 첫번째 객차 가장 큰 애들
// DP[1] : 객차 2개 가장 큰 애들
// DP[2] : 객차 3개 가장 큰 애들
// 점화식 : DP[n][i] = max(DP[n][i-1], DP[n-1][i-m] + i번째부터 소형 객차 값)


int train[50002];
int sum[50002]; // sum[i] : i번째까지의 총 객차 합
int DP[3][50002];

int main()
{
	int n, m;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> train[i];
		sum[i] = sum[i - 1] + train[i];
	}
	cin >> m;

	// 첫번째 객차 가장 큰 애들 찾기
	DP[0][1] = sum[1 + m - 1] - sum[1 - 1];
	for (int i = 2; i <= n - m + 1; i++)
	{
		DP[0][i] = max(DP[0][i - 1], sum[i + m - 1] - sum[i - 1]);
	}

	// 두번째 객차
	// 무조건 M + 1부터 시작 (그 전까지는 객차 1개)
	DP[1][m + 1] = DP[0][1] + sum[m + m] - sum[m];
	for (int i = m + 2; i <= n - m + 1; i++)
	{
		DP[1][i] = max(DP[1][i - 1], DP[0][i - m] + sum[i + m - 1] - sum[i - 1]);
	}

	// 세번째 객차
	int max1 = 0;
	DP[2][m * 2 + 1] = DP[1][m + 1] + sum[m * 2 + 1 + m - 1] - sum[m * 2];
	max1 = DP[2][m * 2 + 1];
	for (int i = m * 2 + 2; i <= n - m + 1; i++)
	{
		DP[2][i] = max(DP[2][i - 1], DP[1][i - m] + sum[i + m - 1] - sum[i - 1]);
		if (DP[2][i] > max1) max1 = DP[2][i];
	}

	cout << max1;

	return 0;
}