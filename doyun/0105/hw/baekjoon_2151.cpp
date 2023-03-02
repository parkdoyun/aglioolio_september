#include <iostream>
#include <queue>

using namespace std;

// 백준 2151 - 거울 설치
// BFS
// 골드 3

// 시간 초과
// 거울 두가지 방법으로 기울일 수 있음
// BFS를 하면서 바로 느낌표 나오면 두개 방향 모두 BFS에 넣기(거울 대각선 방향에 따라)

int n;
int chk[4][51][51];
char board[51][51];
int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };
int sy, sx;

int min1 = 1000000;

void chkClear()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int r = 0; r < 4; r++) chk[r][i][j] = 0;
		}
	}
}

struct node
{
	int y;
	int x;
	int dir; // direction
	int mir_cnt = 0;
};
bool operator<(node n1, node n2)
{
	return n1.mir_cnt > n2.mir_cnt;
}
priority_queue<node> pq;

void BFS()
{
	chkClear();
	while (!pq.empty()) pq.pop();

	chk[0][sy][sx] = 1;
	chk[1][sy][sx] = 1;
	chk[2][sy][sx] = 1;
	chk[3][sy][sx] = 1;

	pq.push({ sy, sx, 0 });
	pq.push({ sy, sx, 1 });
	pq.push({ sy, sx, 2 });
	pq.push({ sy, sx, 3 });

	int ty, tx;

	while (!pq.empty())
	{
		node tmp = pq.top();
		pq.pop();

		ty = tmp.y + y_mov[tmp.dir];
		tx = tmp.x + x_mov[tmp.dir];

		while (ty >= 0 && ty < n && tx >= 0 && tx < n && chk[tmp.dir][ty][tx] == 0)
		{
			chk[tmp.dir][ty][tx] = 1;
			if (board[ty][tx] == '#')
			{
				if (tmp.mir_cnt < min1) min1 = tmp.mir_cnt;
				break;
			}
			else if (board[ty][tx] == '*') break;
			else if (board[ty][tx] == '!')
			{
				if (tmp.dir == 0)
				{
					pq.push({ ty, tx, 3, tmp.mir_cnt + 1 });
					pq.push({ ty, tx, 2, tmp.mir_cnt + 1 });
				}
				else if (tmp.dir == 1)
				{
					pq.push({ ty, tx, 2, tmp.mir_cnt + 1 });
					pq.push({ ty, tx, 3, tmp.mir_cnt + 1 });
				}
				else if (tmp.dir == 2)
				{
					pq.push({ ty, tx, 1, tmp.mir_cnt + 1 });
					pq.push({ ty, tx, 0, tmp.mir_cnt + 1 });
				}
				else
				{
					pq.push({ ty, tx, 0, tmp.mir_cnt + 1 });
					pq.push({ ty, tx, 1, tmp.mir_cnt + 1 });
				}
				//break;
			}
			ty += y_mov[tmp.dir];
			tx += x_mov[tmp.dir];
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	sy = -1;
	sx = -1;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) {
			cin >> board[i][j];
			if (sy == -1 && board[i][j] == '#')
			{
				sy = i;
				sx = j;
			}
		}
	}

	BFS();

	cout << min1;

	return 0;
}
