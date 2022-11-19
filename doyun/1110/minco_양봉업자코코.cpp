#include <iostream>

using namespace std;

// 민코딩 - 양봉업자 코코
// DFS, backtracking

// 가능한 모든 가짓수 계산
// 그 중 최댓값 출력
// 홀수 열이냐 짝수 열이냐에 따라 접근 배열 다름
// 한자리에서 두개까지 뻗을 수 있음

int n, m;
long long max1 = 0;
long long arr[16][16];
int chk[16][16];
int y_mov_o[] = { -1, 0, 0, 1, 1, 1 }; // 홀수 행
int x_mov_o[] = { 0, -1, 1, -1, 0, 1 };
int y_mov_e[] = { -1, -1, -1, 0, 0, 1 }; // 짝수 행
int x_mov_e[] = { -1, 0, 1, -1, 1, 0 };

void DFS(int y, int x, int lv, long long tmp)
{
	if (lv > 4) return;
	if (lv == 4)
	{
		if (tmp > max1) max1 = tmp;
		return;
	}

	if (x % 2 == 1) // 홀수 열
	{
		for (int i = 0; i < 6; i++)
		{
			if (y + y_mov_o[i] >= 0 && y + y_mov_o[i] < n &&
				x + x_mov_o[i] >= 0 && x + x_mov_o[i] < m &&
				chk[y + y_mov_o[i]][x + x_mov_o[i]] == 0)
			{
				chk[y + y_mov_o[i]][x + x_mov_o[i]] = 1;
				DFS(y + y_mov_o[i], x + x_mov_o[i], lv + 1, tmp + arr[y + y_mov_o[i]][x + x_mov_o[i]]);
				for (int j = i + 1; j < 6; j++)
				{
					if (y + y_mov_o[j] >= 0 && y + y_mov_o[j] < n &&
						x + x_mov_o[j] >= 0 && x + x_mov_o[j] < m &&
						chk[y + y_mov_o[j]][x + x_mov_o[j]] == 0)
					{
						chk[y + y_mov_o[j]][x + x_mov_o[j]] = 1;
						DFS(y + y_mov_o[j], x + x_mov_o[j], lv + 2, tmp + arr[y + y_mov_o[i]][x + x_mov_o[i]] + arr[y + y_mov_o[j]][x + x_mov_o[j]]);
						chk[y + y_mov_o[j]][x + x_mov_o[j]] = 0;
					}
				}
				chk[y + y_mov_o[i]][x + x_mov_o[i]] = 0;
			}
		}
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			if (y + y_mov_e[i] >= 0 && y + y_mov_e[i] < n &&
				x + x_mov_e[i] >= 0 && x + x_mov_e[i] < m &&
				chk[y + y_mov_e[i]][x + x_mov_e[i]] == 0)
			{
				chk[y + y_mov_e[i]][x + x_mov_e[i]] = 1;
				DFS(y + y_mov_e[i], x + x_mov_e[i], lv + 1, tmp + arr[y + y_mov_e[i]][x + x_mov_e[i]]);
				for (int j = i + 1; j < 6; j++)
				{
					if (y + y_mov_e[j] >= 0 && y + y_mov_e[j] < n &&
						x + x_mov_e[j] >= 0 && x + x_mov_e[j] < m &&
						chk[y + y_mov_e[j]][x + x_mov_e[j]] == 0)
					{
						chk[y + y_mov_e[j]][x + x_mov_e[j]] = 1;
						DFS(y + y_mov_e[j], x + x_mov_e[j], lv + 2, tmp + arr[y + y_mov_e[i]][x + x_mov_e[i]] + arr[y + y_mov_e[j]][x + x_mov_e[j]]);
						chk[y + y_mov_e[j]][x + x_mov_e[j]] = 0;
					}
				}
				chk[y + y_mov_e[i]][x + x_mov_e[i]] = 0;
			}
		}
	}
}

void chkClear()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			chk[i][j] = 0;
		}
	}
}

int main()
{
	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			chk[i][j] = 1;
			DFS(i, j, 1, arr[i][j]);
			chk[i][j] = 0;
		}
	}

	cout << max1;

	return 0;
}