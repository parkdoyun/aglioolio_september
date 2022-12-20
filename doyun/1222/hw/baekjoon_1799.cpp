#include <iostream>

using namespace std;

// 백준 1799 - 비숍
// backtracking
// 골드 1

// backtracking으로 비숍 놓을 수 있는 부분 확인
// 시간 초과

// 한줄 가득 채우는 게 안 겹칠 확률 높다
// (가로로) 각 한줄씩 전부 채운 상태에서 다른 줄 비교
// 최댓값 출력
// 세로 한줄씩도 채워보자

int board[11][11];
int chk[11][11]; // 비숍이 놓일 수 없는 부분(다른 비숍에 의해)
int n;
int max1 = 0;

void chkClear()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) chk[i][j] = 0;
	}
}
void printBishop(int y, int x, int v) // 비숍에게 위험될 부분 처리
{
	// 왼쪽 위
	int i, j;
	for (i = y - 1, j = x - 1; i >= 0 && j >= 0; i--, j--) chk[i][j] = v;

	// 오른쪽 위
	for (i = y - 1, j = x + 1; i >= 0 && j < n; i--, j++) chk[i][j] = v;

	// 왼쪽 아래
	for (i = y + 1, j = x - 1; i < n && j >= 0; i++, j--) chk[i][j] = v;

	// 오른쪽 아래
	for (i = y + 1, j = x + 1; i < n && j < n; i++, j++) chk[i][j] = v;
}

// 기존 비숍들 건드리지 않는지 확인
int chkBishop(int y, int x)
{
	// 왼쪽 위
	int i, j;
	for (i = y - 1, j = x - 1; i >= 0 && j >= 0; i--, j--) if (chk[i][j] == 1) return -1;

	// 오른쪽 위
	for (i = y - 1, j = x + 1; i >= 0 && j < n; i--, j++) if (chk[i][j] == 1) return -1;

	// 왼쪽 아래
	for (i = y + 1, j = x - 1; i < n && j >= 0; i++, j--) if (chk[i][j] == 1) return -1;

	// 오른쪽 아래
	for (i = y + 1, j = x + 1; i < n && j < n; i++, j++) if (chk[i][j] == 1) return -1;
	return 1;
}

int now_row;
int now_col;
void backtracking(int y, int x, int cnt)
{
	if (max1 < cnt)
	{
		max1 = cnt;
	}

	for (int i = x + 1; i < n; i++) // 기존과 같은 층
	{
		if (i == now_col) continue;
		if (board[y][i] != 1) continue;
		else if (chk[y][i] == 0 && chkBishop(y, i) == 1)
		{
			chk[y][i] = 1;
			printBishop(y, i, 2);
			backtracking(y, i, cnt + 1);
			printBishop(y, i, 0);
			chk[y][i] = 0;
		}
	}
	for (int i = y + 1; i < n; i++)
	{
		if (i == now_row) continue;
		for (int j = 0; j < n; j++)
		{
			if (j == now_col) continue;
			if (board[i][j] != 1) continue;
			else if (chk[i][j] == 0 && chkBishop(i, j) == 1)
			{
				chk[i][j] = 1;
				printBishop(i, j, 2);
				backtracking(i, j, cnt + 1);
				printBishop(i, j, 0);
				chk[i][j] = 0;
			}
		}
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
		for (int j = 0; j < n; j++) cin >> board[i][j];
	}

	int res[11];
	int res2[11];

	int cnt = 0;

	// 가로 한줄씩
	now_col = -1;
	for (int t = 0; t < n; t++)
	{
		cnt = 0;
		chkClear();
		now_row = t;
		max1 = 0;
		// 한줄 채우기
		for (int i = 0; i < n; i++)
		{
			if (board[t][i] != 1) continue;
			else if (chk[t][i] == 0)
			{
				chk[t][i] = 1;
				printBishop(t, i, 2);
				cnt++;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (i == t) continue;
			for (int j = 0; j < n; j++)
			{
				if (board[i][j] != 1) continue;
				else if (chk[i][j] == 0 && chkBishop(i, j) == 1)
				{
					chk[i][j] = 1;
					printBishop(i, j, 2);
					backtracking(i, j, 1);
					printBishop(i, j, 0);
					chk[i][j] = 0;
				}
			}
		}
		res[t] = cnt + max1;
	}

	// 세로 한줄씩
	now_row = -1;
	for (int t = 0; t < n; t++)
	{
		cnt = 0;
		chkClear();
		now_col = t;
		max1 = 0;
		// 한줄 채우기
		for (int i = 0; i < n; i++)
		{
			if (board[i][t] != 1) continue;
			else if (chk[i][t] == 0)
			{
				chk[i][t] = 1;
				printBishop(i, t, 2);
				cnt++;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (i == t) continue;
			for (int j = 0; j < n; j++)
			{
				if (board[j][i] != 1) continue;
				else if (chk[j][i] == 0 && chkBishop(j, i) == 1)
				{
					chk[j][i] = 1;
					printBishop(j, i, 2);
					backtracking(j, i, 1);
					printBishop(j, i, 0);
					chk[j][i] = 0;
				}
			}
		}
		res2[t] = cnt + max1;
	}


	// 최댓값 찾기
	int total_max = res[0];
	for (int i = 1; i < n; i++)
	{
		if (res[i] > total_max) total_max = res[i];
	}
	for (int i = 0; i < n; i++)
	{
		if (res2[i] > total_max) total_max = res2[i];
	}
	cout << total_max;

	return 0;
}