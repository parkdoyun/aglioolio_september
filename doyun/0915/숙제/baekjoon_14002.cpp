#include <iostream>
#include <string>

using namespace std;

// 백준 14002 - 가장 긴 증가하는 부분 수열 4
// LIS, DP
// 골드 4

// max 값 갱신 시 뒤로 가면서 LIS 다시 생성한다

int arr[1001];
int DP[1001];

int main()
{
	int n;
	cin >> n;

	// 기저 조건 
	DP[0] = 1;

	int max = 1; // 기저 조건
	string LIS = "";

	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
		if (i == 0) LIS = to_string(arr[i]);

		int tmp = 0;

		for (int j = 0; j < i; j++)
		{
			if (arr[i] > arr[j] && tmp < DP[j])
			{
				tmp = DP[j];
			}
		}
		DP[i] = tmp + 1;
		if (max < DP[i])
		{
			max = DP[i];

			// LIS 생성
			// 뒤로 가면서 1씩 갱신해가면서 생성

			LIS = to_string(arr[i]);
			int tmp_r = DP[i] - 1;
			for (int j = i - 1; j >= 0; j--)
			{
				if (DP[j] == tmp_r)
				{
					LIS = to_string(arr[j]) + " " + LIS;
					tmp_r--;
				}
			}
		}

	}

	cout << max << '\n' << LIS;

	return 0;

}
