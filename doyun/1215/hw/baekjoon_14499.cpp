#include <iostream>

using namespace std;

// 백준 14499 - 주사위 굴리기
// 구현
// 골드 4

int n, m;
int board[21][21];
int dice[6] = { 0, 0, 0, 0, 0, 0 }; // 초기 주사위 상태
// 1, 6, 2, 3, 5, 4
// 위, 아래, 시계방향으로 옆면

int now_y, now_x;
int y_mov[] = { 0, 0, -1, 1 }; // 동, 서, 북, 남
int x_mov[] = { 1, -1, 0, 0 };
int rotate(int order) // 주사위 회전
{
	if (now_y + y_mov[order] < 0 || now_y + y_mov[order] >= n ||
		now_x + x_mov[order] < 0 || now_x + x_mov[order] >= m) return -1;
	now_y += y_mov[order];
	now_x += x_mov[order];

	// 주사위 회전
	int tmp_d;
	if (order == 0) // 동
	{
		tmp_d = dice[0];
		dice[0] = dice[5];
		dice[5] = dice[1];
		dice[1] = dice[3];
		dice[3] = tmp_d;
	}
	else if (order == 1) // 서
	{
		tmp_d = dice[0];
		dice[0] = dice[3];
		dice[3] = dice[1];
		dice[1] = dice[5];
		dice[5] = tmp_d;
	}
	else if (order == 3) // 남
	{
		tmp_d = dice[0];
		dice[0] = dice[2];
		dice[2] = dice[1];
		dice[1] = dice[4];
		dice[4] = tmp_d;
	}
	else // 2, 북
	{
		tmp_d = dice[0];
		dice[0] = dice[4];
		dice[4] = dice[1];
		dice[1] = dice[2];
		dice[2] = tmp_d;
	}

	return 0;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int x, y, k;
	cin >> n >> m >> y >> x >> k; // 순서 헷갈리지 말기

	now_y = y;
	now_x = x;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> board[i][j];
		}
	}

	int order;
	for (int i = 0; i < k; i++)
	{
		cin >> order;
		if (rotate(--order) == -1) continue;
		if (board[now_y][now_x] == 0)
		{
			board[now_y][now_x] = dice[1];
		}
		else
		{
			dice[1] = board[now_y][now_x];
			board[now_y][now_x] = 0;
		}

		cout << dice[0] << '\n';
	}


	return 0;
}