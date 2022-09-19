#include <iostream>

using namespace std;

// 백준 11054 - 가장 긴 바이토닉 부분 수열
// DP, LIS
// 골드 4

// 증가하는 가장 긴 부분 수열(LIS) 구하고
// 뒤부터 증가하는 가장 긴 부분 수열 구한다
// 각 인덱스의 총합을 비교하여 최댓값 출력한다.

int arr[1001];
int DP_max[1001];
int DP_min[1001];

int main()
{
	int n;
	cin >> n;

	// 기저 조건 : 나만 있는 수열에서는 최대 길이 1이다
	DP_max[0] = 1;
	DP_min[n-1] = 1;

	// 입력받으면서 LIS 구하기
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
		
		int tmp = 0;
		for (int j = 0; j < i; j++)
		{
			if (arr[i] > arr[j])
			{
				if (tmp < DP_max[j]) tmp = DP_max[j];
			}
		}

		DP_max[i] = tmp + 1;
	}

	// 맨 뒤부터 증가하는 부분 수열 구하기
	for (int i = n-1; i >= 0; i--)
	{
		int tmp = 0;
		for (int j = n-1; j > i; j--)
		{
			if (arr[i] > arr[j])
			{
				if (tmp < DP_min[j]) tmp = DP_min[j];
			}
		}

		DP_min[i] = tmp + 1;
	}

	// 두 배열의 최댓값 찾기

	int max = DP_max[0] + DP_min[0];
	for (int i = 1; i < n; i++)
	{
		if (max < DP_max[i] + DP_min[i]) max = DP_max[i] + DP_min[i];
	}

	cout << max - 1;

	return 0;
}