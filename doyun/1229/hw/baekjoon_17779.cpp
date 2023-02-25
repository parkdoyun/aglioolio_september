#include <iostream>

using namespace std;

// 백준 17779 - 게리맨더링 2
// simulation
// 골드 3

// d1 = 1, d2 = 1부터 d1 = n-1, d2 = n-1까지 전부 다 해보고
// 최솟값 출력
// x, y 잘 봐야함 (거꾸로임)

int n;
int board[21][21];
int chk[21][21];
int min1 = 100000000;
int population[6]; // 인구

void chkClear()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++) chk[i][j] = 0;
	}
}

void chkPopulation(int sx, int sy, int d1, int d2)
{
	chkClear();
	// 만약 d1과 d2한 게 벗어난다면 바로 return
	int ty, tx;
	for (int i = 0; i < d2 + 1; i++)
	{
		if (sy + i <= n && sx + i <= n)
		{
			chk[sx + i][sy + i] = 5;
			tx = sy + i;
			ty = sx + i;
		}
		else return;
	}
	for (int i = 1; i <= d1; i++)
	{
		ty++;
		tx--;
		if (ty <= n && tx >= 1)
		{
			chk[ty][tx] = 5;
		}
		else return;
	}
	for (int i = 1; i <= d2; i++)
	{
		ty--;
		tx--;
		if (ty >= 1 && tx >= 1)
		{
			chk[ty][tx] = 5;
		}
		else return;
	}
	for (int i = 1; i < d1; i++)
	{
		ty--;
		tx++;
		if (ty >= 1 && tx <= n)
		{
			chk[ty][tx] = 5;
		}
		else return;
	}

	// chk 마저 채우기
	// 1
	for (int i = 1; i <= sy; i++)
	{
		for (int j = 1; j < sx + d1; j++)
		{
			if (chk[j][i] == 5) break;
			chk[j][i] = 1;
		}
	}

	// 2
	for (int i = sy + 1; i <= n; i++)
	{
		for (int j = 1; j <= sx + d2; j++)
		{
			if (chk[j][i] == 5) break;
			chk[j][i] = 2;
		}
	}

	// 3
	for (int j = n; j >= sx + d1; j--)
	{
		for (int i = 1; i < sy - d1 + d2; i++)
		{
			if (chk[j][i] == 5) break;
			chk[j][i] = 3;
		}
	}

	// 4
	for (int i = sy - d1 + d2; i <= n; i++)
	{
		for (int j = n; j > sx + d2; j--)
		{
			if (chk[j][i] == 5) break;
			chk[j][i] = 4;
		}
	}

	// 5
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (chk[i][j] == 0) chk[i][j] = 5;
		}
	}
	
	// 계산
	for (int i = 1; i <= 5; i++) population[i] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++) population[chk[i][j]] += board[i][j];
	}
	int tmp_max = population[1];
	int tmp_min = population[1];
	for (int i = 2; i <= 5; i++)
	{
		if (tmp_max < population[i]) tmp_max = population[i];
		if (tmp_min > population[i]) tmp_min = population[i];
	}
	if (min1 > tmp_max - tmp_min) min1 = tmp_max - tmp_min;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> board[i][j];
		}
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			for (int r = 1; r <= n - 2; r++)
			{
				for (int k = 1; k <= n - 2; k++)
				{
					chkPopulation(i, j, r, k);
				}
			}
		}
	}
	cout << min1;

	return 0;
}