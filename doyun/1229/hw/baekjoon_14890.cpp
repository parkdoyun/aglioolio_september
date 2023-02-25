#include <iostream>

using namespace std;

// 백준 14890 - 경사로
// simulation
// 골드 3

// 안 되는 경우
// 1. 높이 차이가 1 이상 날 경우
// 2. 평지 길이가 경사로 길이보다 작을 경우

// 가장 높은 최대 높이가 여러 곳일수도 있다

int n, l;
int board[101][101];
int chk[101][101]; // 경사로 체크

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> l;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) cin >> board[i][j];
	}

	int cnt = 0;
	int max1, max_idx, tmp, flag, tmp_height;
	// 가로 줄
	for (int i = 0; i < n; i++)
	{
		// 확인
		// 앞부터
		flag = 0;
		tmp = n-1;
		while (tmp >= 1)
		{
			if (board[i][tmp] + 1 < board[i][tmp - 1])
			{
				flag = 1;
				break;
			}
			else if (board[i][tmp] > board[i][tmp - 1] + 1)
			{
				flag = 1;
				break;
			}
			else if (board[i][tmp] == board[i][tmp - 1] + 1)
			{
				// 경사로 길이만큼 평지 있는지 확인
				int tmp_cnt = 0;
				tmp_height = board[i][tmp - 1];
				for (int j = 1; j <= l; j++)
				{
					if (tmp - j < 0 || board[i][tmp - j] != tmp_height || 
						chk[i][tmp-j] == 1) break;
					tmp_cnt++;
				}
				if (tmp_cnt == l) // ok
				{
					// 경사로 놓기
					for (int j = 1; j <= l; j++)
					{
						chk[i][tmp - j] = 1;
					}
					tmp -= l;
				}
				else
				{
					flag = 1;
					break;
				}
			}
			else if (board[i][tmp] + 1 == board[i][tmp - 1]) // 내 뒤로 놓을 수 있어야 함
			{
				// 경사로 길이만큼 평지 있는지 확인
				int tmp_cnt = 0;
				tmp_height = board[i][tmp];
				for (int j = 0; j < l; j++)
				{
					if (tmp + j >= n || board[i][tmp + j] != tmp_height ||
						chk[i][tmp + j] == 1) break;
					tmp_cnt++;
				}
				if (tmp_cnt == l) // ok
				{
					// 경사로 놓기
					for (int j = 0; j < l; j++)
					{
						chk[i][tmp + j] = 1;
					}
					tmp--;
				}
				else
				{
					flag = 1;
					break;
				}
			}
			else tmp--;
		}
		if (flag == 1) continue;
		cnt++;
	}
	
	// chk clear
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) chk[i][j] = 0;
	}

	// 세로줄
	for (int i = 0; i < n; i++)
	{
		// 확인
		// 앞부터
		flag = 0;
		tmp = n - 1;
		while (tmp >= 1)
		{
			if (board[tmp][i] + 1 < board[tmp - 1][i])
			{
				flag = 1;
				break;
			}
			else if (board[tmp][i] > board[tmp - 1][i] + 1)
			{
				flag = 1;
				break;
			}
			else if (board[tmp][i] == board[tmp - 1][i] + 1)
			{
				// 경사로 길이만큼 평지 있는지 확인
				int tmp_cnt = 0;
				tmp_height = board[tmp - 1][i];
				for (int j = 1; j <= l; j++)
				{
					if (tmp - j < 0 || board[tmp - j][i] != tmp_height || chk[tmp - j][i] == 1) break;
					tmp_cnt++;
				}
				if (tmp_cnt >= l) // ok
				{
					for (int j = 1; j <= l; j++)
					{
						chk[tmp - j][i] = 1;
					}
					tmp -= l;
				}
				else
				{
					flag = 1;
					break;
				}
			}
			else if (board[tmp][i] + 1 == board[tmp - 1][i])
			{
				int tmp_cnt = 0;
				tmp_height = board[tmp][i];
				for (int j = 0; j < l; j++)
				{
					if (tmp + j >= n || board[tmp + j][i] != tmp_height || chk[tmp + j][i] == 1) break;
					tmp_cnt++;
				}
				if (tmp_cnt >= l) // ok
				{
					for (int j = 0; j < l; j++)
					{
						chk[tmp + j][i] = 1;
					}
					tmp--;
				}
				else
				{
					flag = 1;
					break;
				}
			}
			else tmp--;
		}
		if (flag == 1) continue;

		cnt++;
	}

	cout << cnt;

	return 0;
}