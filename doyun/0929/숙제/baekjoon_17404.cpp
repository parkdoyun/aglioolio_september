#include <iostream>

using namespace std;

// 백준 17404 - RGB 거리2
// DP
// 골드 4

// 첫번째 값 고정 후 (r/g/b) 
// ex 첫번째가 r일 때) 이 첫번째 값으로부터 나올 수 있는 세가지 경우의 수 모두 구한다.(맨 마지막의 g,b만 확인하면 됨)
// 그 중 r에서 나올 수 있는 값 두개(마지막 g, b) 중 최소 선택 => r이 시작일 때의 최소값
// 이렇게 g, b에서 시작하는 애들도 구해서
// 세개 중 최소 구하면 된다.

int arr[1001][3];
int DP[1002][3];

int min_val[3]; // 최소 넣을 공간

int main()
{
	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> arr[i][j];
		}
	}

	for (int r = 0; r < 3; r++)
	{
		for (int i = 0; i < 3; i++) // 첫번째 대상 제외하고 큰 값으로 만들기 => 처음에 선택 안 돼서 r로 시작된 애들만 DP 되도록
		{
			if (i == r) DP[0][i] = arr[0][i];
			else DP[0][i] = 10000001;
		}

		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				
				if (j == 0)
				{
					DP[i][j] = arr[i][j] + (DP[i - 1][1] < DP[i - 1][2] ? DP[i - 1][1] : DP[i - 1][2]);
				}
				else if (j == 1)
				{
					DP[i][j] = arr[i][j] + (DP[i - 1][0] < DP[i - 1][2] ? DP[i - 1][0] : DP[i - 1][2]);
				}
				else // j == 2
				{
					DP[i][j] = arr[i][j] + (DP[i - 1][1] < DP[i - 1][0] ? DP[i - 1][1] : DP[i - 1][0]);
				}
			
			}
		}

		// 최소 넣기
		int min = 10000000;
		for (int i = 0; i < 3; i++)
		{
			if (i == r) continue;
			if (min > DP[n - 1][i]) min = DP[n - 1][i];
		}
		min_val[r] = min;
	}

	// 셋 중 최소 출력
	int min = 10000000;

	for (int i = 0; i < 3; i++)
	{
		if (min_val[i] < min) min = min_val[i];
	}

	cout << min;

	return 0;
}