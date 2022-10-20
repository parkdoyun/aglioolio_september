#include <iostream>
#include <queue>

using namespace std;

// 백준 2206 - 벽 부수고 이동하기
// bfs

// 한개씩 부순 거 다 해보기
// dfs, backtracking -> 시간초과
// bfs로 바꿔보자 => 메모리 초과
// chk => 벽 부순 거랑 안 부순 거랑 구분

int n, m;

int board[1001][1001];
int chk[2][1001][1001]; // chk[0] : 한번도 벽 안 부숨, chk[1] : 벽 한번 부숨

int x_mov[] = { 0, 1, -1, 0 };
int y_mov[] = { 1, 0, 0, -1 };

struct node
{
	int y;
	int x;
	int dist;
	int flag = 0;
};

bool operator<(node n1, node n2)
{
	if (n1.dist > n2.dist) return true;
	return false;
}

priority_queue<node> pq;

int BFS(int y, int x)
{
	pq.push({ y, x, 1, 0 });

	while (!pq.empty())
	{
		node tmp = pq.top();
		pq.pop();
		if (tmp.y == n - 1 && tmp.x == m - 1)
		{
			return tmp.dist;
		}
		if (chk[tmp.flag][tmp.y][tmp.x] == 1) continue;
		chk[tmp.flag][tmp.y][tmp.x] = 1;

		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 0 && tmp.y + y_mov[i] < n &&
				tmp.x + x_mov[i] >= 0 && tmp.x + x_mov[i] < m &&
				chk[tmp.flag][tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0)
			{
				if (tmp.flag == 0 && board[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 1)
				{
					pq.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.dist + 1, 1 });
				}
				else if (board[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0)
				{
					pq.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.dist + 1, tmp.flag });
				}

			}
		}
	}
	return -1;
}


int main()
{
	cin >> n >> m;
	char c;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> c;
			board[i][j] = (int)(c - '0');
		}
	}


	int res = BFS(0, 0);
	cout << res;

	return 0;
}