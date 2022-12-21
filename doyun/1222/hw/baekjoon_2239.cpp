#include <iostream>

using namespace std;

// 백준 2239 - 스도쿠
// backtracking
// 골드 4

// simulation으로 풀다가 시간초과 및 오답 -> backtracking
// 1부터 넣으면서 일단 path[]에 0 나오는 거 없으면 다음으로 넘김

int board[10][10];

void pathChk(int y, int x, int path[10]) // board[y][x]에 들어갈 수 있는 수 구함
{
	// 가로줄 확인
	for (int i = 0; i < 9; i++)
	{
		path[board[y][i]]++;
	}
	// 세로줄 확인
	for (int i = 0; i < 9; i++)
	{
		path[board[i][x]]++;
	}
	// 상자 확인
	int sy = y - (y % 3);
	int sx = x - (x % 3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			path[board[sy + i][sx + j]]++;
		}
	}
}

int total_flag = 0;
void backtracking(int y, int x) // 내 다음 빈칸만 체크하면 됨
{
	if (total_flag == 1) return;
	int tmp_path[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	// 가로, 세로, 상자 확인해서 넣을 수 있는 수들 순서대로 넣고 backtracking
	// 채울 수 있는 수가 없다면 return
	// 해당 수로 할 수 있는 게 없다 -> 이전 재귀로 돌아와서 다음 수로 채움

	int flag = 0;

	int ty = -1; // 내 다음 빈칸
	int tx = -1;
	for (int i = x + 1; i < 9; i++)
	{
		if (board[y][i] == 0)
		{
			ty = y;
			tx = i;
			break;
		}
	}
	if (ty == -1 && tx == -1)
	{
		for (int i = y + 1; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (board[i][j] == 0)
				{
					ty = i;
					tx = j;
					break;
				}
			}
			if (ty != -1) break;
		}
	}
	// 또 ty와 tx -1 => 스도쿠 완성(다음 빈칸들 중 더 이상 0인 애들 없음)
	if (ty == -1 && tx == -1)
	{
		total_flag = 1;
		return;
	}
	else // 아니라면 다음 빈칸 채우기
	{
		for (int j = 0; j <= 9; j++) tmp_path[j] = 0;
		pathChk(ty, tx, tmp_path);
		for (int j = 1; j <= 9; j++)
		{
			if (tmp_path[j] != 0) continue;
			board[ty][tx] = j;
			backtracking(ty, tx);
			if (total_flag == 1) return;
			board[ty][tx] = 0;
		}
	}

}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	char c;
	int sy = -1;
	int sx = -1;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cin >> c;
			board[i][j] = (int)(c - '0');
			if (board[i][j] == 0 && sy == -1 && sx == -1)
			{
				sy = i;
				sx = j;
			}
		}
	}

	int tmp_path[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	pathChk(sy, sx, tmp_path);
	for (int i = 1; i <= 9; i++)
	{
		if (tmp_path[i] != 0) continue;
		board[sy][sx] = i;
		backtracking(sy, sx);
		if (total_flag == 1) break;
		board[sy][sx] = 0;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) cout << board[i][j];
		cout << '\n';
	}

	return 0;
}