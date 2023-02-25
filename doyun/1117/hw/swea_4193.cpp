#include <iostream>
#include <queue>

using namespace std;

// swea 4193 - 수영대회 결승전
// BFS

// 모든 경우의 수 다 하기
// 시간 재면서 해야 함 -> BFS
// 소용돌이 -> 3 * n초에 건널 수 있음

int n, y1_s, x1_s, y2_e, x2_e;
int min1 = 1000000000;
int board[16][16];
int chk[16][16];
int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };

void chkClear()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			chk[i][j] = 0;
		}
	}
}

struct node
{
	int y;
	int x;
	int time;
};

bool operator<(node n1, node n2)
{
	if (n1.time > n2.time) return true;
	return false;
}

priority_queue<node> pq;
void BFS()
{
	chkClear();
	while (!pq.empty()) pq.pop();

	pq.push({ y1_s, x1_s, 0 });

	while (!pq.empty())
	{
		node tmp = pq.top();
		pq.pop();

		if (chk[tmp.y][tmp.x] == 1) continue;
		chk[tmp.y][tmp.x] = 1;
		if (tmp.y == y2_e && tmp.x == x2_e)
		{
			if (tmp.time < min1) min1 = tmp.time;
		}

		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 0 && tmp.y + y_mov[i] < n &&
				tmp.x + x_mov[i] >= 0 && tmp.x + x_mov[i] < n &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0 &&
				board[tmp.y + y_mov[i]][tmp.x + x_mov[i]] != 1)
			{
				if (board[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 2)
				{
					int remainder = tmp.time % 3;
					int new_time = tmp.time - remainder + 3;
					pq.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], new_time });
				}
				else // 0
				{
					pq.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.time + 1 });
				}
			}
		}
	}
}

int main()
{
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> n;
		min1 = 1000000000;
		
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++) cin >> board[i][j];
		}

		cin >> y1_s >> x1_s >> y2_e >> x2_e;

		BFS();

		if (min1 == 1000000000) min1 = -1;
		cout << '#' << tc << ' ' << min1 << '\n';
	}


	return 0;
}