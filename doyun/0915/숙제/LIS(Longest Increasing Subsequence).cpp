#include <iostream>

using namespace std;

// 백준 11053 - 가장 긴 증가하는 부분 수열
// LIS (Longest Increasing Subsequence), DP
// 실버 2

int arr[1001];
int DP[1001];

int main()
{
	int n;
	cin >> n;

	// 기저 조건 : 하나만 있을 때 가장 긴 수열의 길이는 1이다
	DP[0] = 1;

	int max = -1;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
		int tmp = 0;
		for (int j = 0; j < i; j++)
		{
			if (arr[i] > arr[j])
			{
				if (tmp < DP[j]) tmp = DP[j];
			}
		}

		DP[i] = tmp + 1;
		if (DP[i] > max) max = DP[i];
	}

	// 꼭 마지막 값이 최대인 것은 아니다
	cout << max;

	return 0;
}