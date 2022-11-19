#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// swea 1953 - 탈주범 검거
// bfs
// 블럭 모양대로 이동
// 배관 반대쪽도 맞아야 가능!

int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };

int n, m, r, c, l;
int board[51][51];
int chk[51][51];

vector<vector<int>> blocks = { {},  {0, 1, 2, 3}, {0, 1},
	{2, 3}, {0, 3}, {1, 3}, {1, 2}, {0, 2} };

struct node
{
	int y;
	int x;
	int time = 0;
	int dir; // 0 : 상, 1 : 하, 2 : 좌, 3 : 우
};

bool operator<(node n1, node n2)
{
	if (n1.time > n2.time) return true;
	return false;
}
priority_queue<node> pq;

int cnt;
void BFS()
{
	while (!pq.empty()) pq.pop();

	pq.push({ r, c, 0 });

	while (!pq.empty())
	{
		node tmp = pq.top();
		pq.pop();

		if (chk[tmp.y][tmp.x] == 1) continue;
		if (tmp.time >= l) break;

		// 배관 방향 확인
		int val = board[tmp.y][tmp.x];
		int flag = -1;
		if (!(tmp.y == r && tmp.x == c)) // 처음 칸 제외
		{
			if (tmp.dir == 0)
			{
				for (int i = 0; i < blocks[val].size(); i++)
				{
					if (blocks[val][i] == 1)
					{
						flag = 1;
						break;
					}
				}
			}
			else if (tmp.dir == 1)
			{
				for (int i = 0; i < blocks[val].size(); i++)
				{
					if (blocks[val][i] == 0)
					{
						flag = 1;
						break;
					}
				}
			}
			else if (tmp.dir == 2)
			{
				for (int i = 0; i < blocks[val].size(); i++)
				{
					if (blocks[val][i] == 3)
					{
						flag = 1;
						break;
					}
				}
			}
			else // 3
			{
				for (int i = 0; i < blocks[val].size(); i++)
				{
					if (blocks[val][i] == 2)
					{
						flag = 1;
						break;
					}
				}
			}
			if (flag == -1)  continue;
		}

		chk[tmp.y][tmp.x] = 1;
		cnt++;

		for (int i = 0; i < blocks[val].size(); i++)
		{
			if (tmp.y + y_mov[blocks[val][i]] >= 0 && tmp.y + y_mov[blocks[val][i]] < n &&
				tmp.x + x_mov[blocks[val][i]] >= 0 && tmp.x + x_mov[blocks[val][i]] < m &&
				chk[tmp.y + y_mov[blocks[val][i]]][tmp.x + x_mov[blocks[val][i]]] == 0 && 
				board[tmp.y + y_mov[blocks[val][i]]][tmp.x + x_mov[blocks[val][i]]] != 0)
			{
				// 배관 반대쪽도 확인해야 함

				pq.push({ tmp.y + y_mov[blocks[val][i]] , tmp.x + x_mov[blocks[val][i]], tmp.time + 1, blocks[val][i] });
			}
		}

	}

}
void chkClear()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) chk[i][j] = 0;
	}
}
int main()
{
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		cin >> n >> m >> r >> c >> l;

		chkClear();

		cnt = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++) cin >> board[i][j];
		}

		BFS();

		cout << '#' << tc << ' ' << cnt << '\n';
	}

	return 0;
}