#include <iostream>
#include <queue>

using namespace std;

// 백준 16946 - 벽 부수고 이동하기 4
// DFS
// 골드 2

// 1. backtracking
// 시간 초과
// 1000 * 1000 크기라 다른 방법 필요
// 2. BFS => 시간 초과

// DP?
// DP[i][j] = 1 + DP[i-1][j] + DP[i+1][j] + DP[i][j-1] + DP[i][j+1]; (벽 아닌 애들)

// 3. DFS
// 0인 곳들 전부 조사 (연결된 곳 라벨링)
// 어차피 다 연결되었으면 가는 곳 같음
// arr[i][j] = 1 + arr[i-1][j](얘가 포함된 구역의 크기) + arr[i+1][j] + arr[i][j-1] + arr[i][j+1]; (벽 아닌 애들)
// 구역 4개(상하좌우) 중복 제거해야 함

int n, m;
int chk[1001][1001];
int board[1001][1001];
int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };
int block_n[1000005]; // 라벨링한 곳 총 몇개의 블록인지

void labeling(int y, int x, int a) // 라벨링
{
	block_n[a]++;
	board[y][x] = a;
	int ty, tx;
	for (int i = 0; i < 4; i++)
	{
		ty = y + y_mov[i];
		tx = x + x_mov[i];
		if (ty >= 0 && ty < n && tx >= 0 && tx < m &&
			board[ty][tx] == 0 && chk[ty][tx] == 0)
		{
			chk[ty][tx] = 1;
			labeling(ty, tx, a);
		}
	}
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
			if (c == '0') board[i][j] = 0;
			else board[i][j] = 1;
		}
	}
	// 라벨링
	int idx = 2;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (board[i][j] >= 1 || chk[i][j] == 1) continue;
			chk[i][j] = 1;
			labeling(i, j, idx);
			idx++;
		}
	}

	int path[4];
	int ty, tx;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (board[i][j] != 1)
			{
				cout << 0;
				continue;
			}
			idx = 0;
			for (int k = 0; k < 4; k++)
			{
				ty = i + y_mov[k];
				tx = j + x_mov[k];
				if (ty >= 0 && ty < n && tx >= 0 && tx < m &&
					board[ty][tx] != 1) {
					// 중복 체크
					int flag = 0;
					for (int r = 0; r < idx; r++)
					{
						if (path[r] == board[ty][tx])
						{
							flag = 1;
							break;
						}
					}
					if (flag == 0)
					{
						path[idx] = board[ty][tx];
						idx++;
					}
				}
			}
			int res = 1;
			for (int i = 0; i < idx; i++)
			{
				res += block_n[path[i]];
			}
			cout << res % 10;
		}
		cout << '\n';
	}


	return 0;
}