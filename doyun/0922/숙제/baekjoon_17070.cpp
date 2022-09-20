#include <iostream>

using namespace std;

// 백준 17070 - 파이프 옮기기1
// DP
// 골드 5

// 해당 지점에서 가로로 올 수 있는 가짓수, 세로로 올 수 있는 가짓수,
// 대각선으로 올 수 있는 가짓수를 계산한다.
// 마지막에 가로, 세로, 대각선 가짓수 다 더해서 출력

struct node {
	int row = 0; // 가로로 온 횟수
	int col = 0; // 세로로 온 횟수
	int diag = 0; // 대각선으로 온 횟수
};

int board[17][17];
node DP[17][17];

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> board[i][j];
		}
	}
	
	// 초기 설정
	DP[1][2].row = 1;

	for (int i = 3; i <= n; i++)
	{
		if (board[1][i] == 1) continue;
		DP[1][i] = DP[1][i - 1];
	}

	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (board[i][j] == 1) continue;

			// 가로로 오는 것
			if (j - 1 >= 1)
			{
				// 이전 : 가로
				DP[i][j].row += DP[i][j - 1].row;

				// 이전 : 대각선
				if (i - 1 >= 1) DP[i][j].row += DP[i][j - 1].diag;
			}
			// 세로로 오는 것
			DP[i][j].col += DP[i - 1][j].col;

			// 이전 : 대각선
			if (j - 1 >= 1) DP[i][j].col += DP[i - 1][j].diag;

			// 대각선으로 오는 것
			if (j - 1 >= 1 && board[i][j - 1] == 0 && board[i - 1][j] == 0)
			{
				// 이전 : 대각선
				DP[i][j].diag += DP[i - 1][j - 1].diag;
				// 이전 : 가로
				DP[i][j].diag += DP[i - 1][j - 1].row;
				// 이전 : 세로
				DP[i][j].diag += DP[i - 1][j - 1].col;
			}
			
		}
	}

	cout << DP[n][n].row + DP[n][n].col + DP[n][n].diag;
	
	return 0;
}