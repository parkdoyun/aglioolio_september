#include <iostream>

using namespace std;

// 백준 12100 - 2048 (Easy)
// brute-force, backtracking, 구현
// 골드 2

// 움직일 수 있는 거 상하좌우, 최대 5
// 1. backtracking으로 모든 조합 나눔
// 2. 움직이면서 최대 블록 구함

int n;
int board[21][21];
int board_cp[21][21];
int path[6]; // backtracking, 1:상, 2:하, 3:좌, 4:우
int max1 = 0;

void copy()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) board_cp[i][j] = board[i][j];
	}
}

int move(int dir) // 블록들 움직이고, 최댓값 반환
{
	int tmp_max = 0;
	int tmp_arr[21]; // 블록 움직일 임시 배열
	int idx;

	if (dir == 1) // 상
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++) tmp_arr[j] = 0;
			idx = 0;

			// 애들 몰아넣기
			for (int j = 0; j < n; j++)
			{
				if (board_cp[j][i] == 0) continue;
				tmp_arr[idx] = board_cp[j][i];
				idx++;
				board_cp[j][i] = 0;
			}

			// 하나로 합치기
			idx = 1;
			while (idx < n)
			{
				if (tmp_arr[idx-1] == tmp_arr[idx])
				{
					tmp_arr[idx - 1] *= 2;
					tmp_arr[idx] = 0;
					idx += 2;
				}
				else // 같지 않음 -> 다음으로 넘김
				{
					idx++;
				}
			}

			// 다시 넣기
			idx = 0;
			for (int j = 0; j < n; j++)
			{
				if (tmp_arr[j] == 0) continue;
				board_cp[idx][i] = tmp_arr[j];
				if (tmp_arr[j] > tmp_max) tmp_max = tmp_arr[j];
				idx++;
			}
		}
	}
	else if (dir == 2) // 하
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++) tmp_arr[j] = 0;
			idx = 0;

			// 애들 몰아넣기
			for (int j = n-1; j >= 0; j--)
			{
				if (board_cp[j][i] == 0) continue;
				tmp_arr[idx] = board_cp[j][i];
				idx++;
				board_cp[j][i] = 0;
			}

			// 하나로 합치기
			idx = 1;
			while (idx < n)
			{
				if (tmp_arr[idx - 1] == tmp_arr[idx])
				{
					tmp_arr[idx - 1] *= 2;
					tmp_arr[idx] = 0;
					idx += 2;
				}
				else // 같지 않음 -> 다음으로 넘김
				{
					idx++;
				}
			}

			// 다시 넣기
			idx = n-1;
			for (int j = 0; j < n; j++)
			{
				if (tmp_arr[j] == 0) continue;
				if (tmp_arr[j] > tmp_max) tmp_max = tmp_arr[j];
				board_cp[idx][i] = tmp_arr[j];
				idx--;
			}
		}
	}
	else if (dir == 3) // 좌
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++) tmp_arr[j] = 0;
			idx = 0;

			// 애들 몰아넣기
			for (int j = 0; j < n; j++)
			{
				if (board_cp[i][j] == 0) continue;
				tmp_arr[idx] = board_cp[i][j];
				idx++;
				board_cp[i][j] = 0;
			}

			// 하나로 합치기
			idx = 1;
			while (idx < n)
			{
				if (tmp_arr[idx - 1] == tmp_arr[idx])
				{
					tmp_arr[idx - 1] *= 2;
					tmp_arr[idx] = 0;
					idx += 2;
				}
				else // 같지 않음 -> 다음으로 넘김
				{
					idx++;
				}
			}

			// 다시 넣기
			idx = 0;
			for (int j = 0; j < n; j++)
			{
				if (tmp_arr[j] == 0) continue;
				if (tmp_arr[j] > tmp_max) tmp_max = tmp_arr[j];
				board_cp[i][idx] = tmp_arr[j];
				idx++;
			}
		}
	}
	else // 우
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++) tmp_arr[j] = 0;
			idx = 0;

			// 애들 몰아넣기
			for (int j = n - 1; j >= 0; j--)
			{
				if (board_cp[i][j] == 0) continue;
				tmp_arr[idx] = board_cp[i][j];
				idx++;
				board_cp[i][j] = 0;
			}

			// 하나로 합치기
			idx = 1;
			while (idx < n)
			{
				if (tmp_arr[idx - 1] == tmp_arr[idx])
				{
					tmp_arr[idx - 1] *= 2;
					tmp_arr[idx] = 0;
					idx += 2;
				}
				else // 같지 않음 -> 다음으로 넘김
				{
					idx++;
				}
			}

			// 다시 넣기
			idx = n - 1;
			for (int j = 0; j < n; j++)
			{
				if (tmp_arr[j] == 0) continue;
				if (tmp_arr[j] > tmp_max) tmp_max = tmp_arr[j];
				board_cp[i][idx] = tmp_arr[j];
				idx--;
			}
		}
	}

	return tmp_max;
}

int cal() // 계산
{
	int total_max = 0;
	for (int i = 0; i < 5; i++)
	{
		int tmp = move(path[i]); // 블록들 움직이기
		if (tmp > total_max) total_max = tmp;
	}
	return total_max;
}

void backtracking(int lv)
{
	if (lv == 5)
	{
		// 계산
		copy();
		int res = cal();
		if (res > max1) max1 = res;
		return;
	}

	for (int i = 1; i <= 4; i++)
	{
		path[lv] = i;
		backtracking(lv + 1);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> board[i][j];
		}
	}

	for (int i = 1; i <= 4; i++)
	{
		path[0] = i;
		backtracking(1);
	}
	
	cout << max1;

	return 0;
}