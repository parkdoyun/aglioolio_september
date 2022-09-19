#include <iostream>

using namespace std;

// 백준 2631 - 줄세우기
// DP, LIS
// 골드 4

// LIS 문제
// 몇명 빠졌을 때 최장 증가 수열인지?
// 최장 증가 수열에서 제외된 애들 = 자리 교체하는 애들

int arr[201];
int DP[201];

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	
	// 기저조건
	DP[0] = 1;

	for (int i = 1; i < n; i++) {

		int tmp = 0;
		for (int j = 0; j < i; j++)
		{
			if (arr[i] > arr[j] && tmp < DP[j]) tmp = DP[j];
		}
		DP[i] = tmp + 1;
	}

	int max = DP[0];
	for (int i = 1; i < n; i++)
	{
		if (max < DP[i]) max = DP[i];
	}
	cout << n - max;

	return 0;
}