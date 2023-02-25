#include <iostream>

using namespace std;

// 백준 16724 - 피리 부는 사나이
// DFS
// 골드 3

// cycle의 갯수 세면 된다
// cycle 내부에 safe zone 설치하면 되므로

// 1 만나면 새로운 cycle => cnt++
// 2 만나면 무시(cycle이기도 하지만 이미 cycle 검사 끝난 표시기도 함)

int n, m;
int board[1001][1001];
int chk[1001][1001]; // visit : 1, cycle : 2
int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };
int cnt = 0;

void search(int y, int x)
{
	chk[y][x] = 1;
	int ty = y + y_mov[board[y][x]];
	int tx = x + x_mov[board[y][x]];
	if (chk[ty][tx] == 1) cnt++; // cycle 생김
	else if (chk[ty][tx] == 0) search(ty, tx);
	chk[y][x] = 2; // 마지막 나올 때는 무조건 2로 바꿔야 헷갈리지 않음
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	char c;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> c;
			if (c == 'U') board[i][j] = 0;
			else if (c == 'D') board[i][j] = 1;
			else if (c == 'L') board[i][j] = 2;
			else board[i][j] = 3;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (chk[i][j] == 0) search(i, j);
		}
	}

	cout << cnt;

	return 0;
}