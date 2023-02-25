#include <iostream>

using namespace std;

// 백준 20057 - 마법사 상어와 토네이도
// simulation
// 골드 3

// 격자의 밖으로 이동한 모래 = 토네이도 흩날리기 전 모래 양 - 남은 모래

int n;
int sand[501][501];

int y_mov[] = { 0, 1, 0, -1 }; // 0 좌, 1 하, 2 우, 3 상
int x_mov[] = { -1, 0, 1, 0 };

// 모래 비율
int sand_proposition[9] = { 2, 10, 7, 1, 5, 10, 7, 1, 2 };

// 이동하는 모래 방향
int sand_dir_x[4][9] =
{
	{0, -1, 0, 1, -2, -1, 0, 1, 0}, // 좌
	{2, 1, 1, 1, 0, -1, -1, -1, -2}, // 하
	{0, 1, 0, -1, 2, 1, 0, -1, 0}, // 우
	{2, 1, 1, 1, 0, -1, -1, -1, -2} // 상
};

int sand_dir_y[4][9] =
{
	{-2, -1, -1, -1, 0, 1, 1, 1, 2}, // 좌
	{0, 1, 0, -1, 2, 1, 0, -1, 0}, // 하
	{-2, -1, -1, -1, 0, 1, 1, 1, 2}, // 우
	{0, -1, 0, 1, -2, -1, 0, 1, 0}, // 상
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	int total = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> sand[i][j];
			total += sand[i][j];
		}
	}

	int sy = n / 2;
	int sx = n / 2;
	int dir = 0;


	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int r = 0; r < i; r++)
			{
				sy += y_mov[dir];
				sx += x_mov[dir];

				// 모래 흩날리기
				int now = sand[sy][sx];
				int tmp = sand[sy][sx]; // alpha에 넣을 것
				for (int r = 0; r < 9; r++)
				{
					if (sy + sand_dir_y[dir][r] >= 0 && sy + sand_dir_y[dir][r] < n &&
						sx + sand_dir_x[dir][r] >= 0 && sx + sand_dir_x[dir][r] < n)
					{
						sand[sy + sand_dir_y[dir][r]][sx + sand_dir_x[dir][r]] += (int)(now * sand_proposition[r] / 100);
						//tmp -= (int)(now * sand_proposition[r] / 100);
					}
					tmp -= (int)(now * sand_proposition[r] / 100);
				}
				sand[sy][sx] = 0;
				if (sy + y_mov[dir] >= 0 && sy + y_mov[dir] < n &&
					sx + x_mov[dir] >= 0 && sx + x_mov[dir] < n)
				{
					sand[sy + y_mov[dir]][sx + x_mov[dir]] += tmp;
				}
			}
			dir++;
			dir = dir % 4;
		}
	}

	// 마지막으로 한번 더 가야함

	for (int r = 0; r < n - 1; r++)
	{
		sy += y_mov[dir];
		sx += x_mov[dir];

		// 모래 흩날리기
		int now = sand[sy][sx];
		int tmp = sand[sy][sx]; // alpha에 넣을 것
		for (int r = 0; r < 9; r++)
		{
			if (sy + sand_dir_y[dir][r] >= 0 && sy + sand_dir_y[dir][r] < n &&
				sx + sand_dir_x[dir][r] >= 0 && sx + sand_dir_x[dir][r] < n)
			{
				sand[sy + sand_dir_y[dir][r]][sx + sand_dir_x[dir][r]] += (int)(now * sand_proposition[r] / 100);
				//tmp -= (int)(now * sand_proposition[r] / 100);
			}
			tmp -= (int)(now * sand_proposition[r] / 100);
		}
		sand[sy][sx] = 0;
		if (sy + y_mov[dir] >= 0 && sy + y_mov[dir] < n &&
			sx + x_mov[dir] >= 0 && sx + x_mov[dir] < n)
		{
			sand[sy + y_mov[dir]][sx + x_mov[dir]] += tmp;
		}
	}

	int minus_val = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			minus_val += sand[i][j];
		}
	}
	
	cout << total - minus_val;


	return 0;
}