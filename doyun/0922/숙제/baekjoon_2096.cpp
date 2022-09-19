#include <iostream>

using namespace std;

// 백준 2096 - 내려가기
// DP
// 골드 5

// 똑같은 배열 하나 만들어놓고
// 내려가면서 모든 수 계산 (이미 수가 있다면 최소/최대일 경우 갱신)
// 최대, 최소 각 계산 배열 하나씩 -> 메모리초과

// 원래 입력 값 저장할 배열 필요 X
// 최대, 최소 배열 두개씩만 있어도 됨! (바로 이전꺼랑 이번에 갱신할 내용)
// for문 돌아가면서 넣어주기

int DP_min[2][3];
int DP_max[2][3];

int main()
{
	int n;
	cin >> n;

	int a;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> a;
			if (i == 0)
			{
				DP_min[0][j] = a;
				DP_max[0][j] = a;
			}
			else // i > 0
			{
				// max
				int tmp_max = DP_max[0][j];
				if (j - 1 >= 0 && tmp_max < DP_max[0][j - 1]) tmp_max = DP_max[0][j - 1];
				if (j + 1 < 3 && tmp_max < DP_max[0][j + 1]) tmp_max = DP_max[0][j + 1];
				DP_max[1][j] = tmp_max + a;

				// min
				int tmp_min = DP_min[0][j];
				if (j - 1 >= 0 && tmp_min > DP_min[0][j - 1]) tmp_min = DP_min[0][j - 1];
				if (j + 1 < 3 && tmp_min > DP_min[0][j + 1]) tmp_min = DP_min[0][j + 1];
				DP_min[1][j] = tmp_min + a;
			}

			
		}
		// 앞줄로 땡기기
		if (i != 0)
		{
			for (int r = 0; r < 3; r++)
			{
				DP_min[0][r] = DP_min[1][r];
				DP_max[0][r] = DP_max[1][r];
			}
		}
	}

	// 맨 마지막 줄 (n-1) 최대, 최소 출력
	int max = DP_max[0][0];
	for (int i = 1; i < 3; i++)
	{
		if (max < DP_max[0][i]) max = DP_max[0][i];
	}

	int min = DP_min[0][0];
	for (int i = 1; i < 3; i++)
	{
		if (min > DP_min[0][i]) min = DP_min[0][i];
	}

	cout << max << ' ' << min;

	return 0;
}