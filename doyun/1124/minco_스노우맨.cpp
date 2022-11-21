#include <iostream>
#include <queue>

using namespace std;

// 민코딩 - 스노우맨
// dijkstra

// DFS => dijkstra
// 최대 점프 -> limit 갱신
// 도착 시 limit 값 비교 -> 최솟값

int board[51][51];
int chk[51][51];

int n, m;
int min1 = 100000000;
int start_y, start_x, end_y, end_x;
int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };

struct node
{
	int y;
	int x;
	int limit;
	int max_limit;
};

bool operator<(node n1, node n2)
{
	if (n1.max_limit > n2.max_limit) return true;
	else if (n1.max_limit == n2.max_limit && n1.limit > n2.limit) return true;
	return false;	
}

priority_queue<node> pq;
void BFS()
{
	while (!pq.empty()) pq.pop();

	pq.push({ start_y, start_x, 0, 0});

	while (!pq.empty())
	{
		node tmp = pq.top();
		pq.pop();

		if (chk[tmp.y][tmp.x] == 1) continue;
		chk[tmp.y][tmp.x] = 1;

		if (board[tmp.y][tmp.x] == 1) tmp.limit = 0;

		if (tmp.limit > min1) break;

		if (tmp.y == end_y && tmp.x == end_x)
		{
			if (tmp.max_limit < min1) min1 = tmp.max_limit;
			continue;
		}

		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 0 && tmp.y + y_mov[i] < n &&
				tmp.x + x_mov[i] >= 0 && tmp.x + x_mov[i] < m &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0)
			{
				if (i == 0 || i == 1)
				{
					if (tmp.max_limit < tmp.limit + 1) pq.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.limit + 1, tmp.limit + 1});
					else pq.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.limit + 1, tmp.max_limit});
				}
				else // 좌우 이동
				{
					if (board[tmp.y][tmp.x] == 0) continue;
					if (board[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0) continue;
					pq.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.limit, tmp.max_limit});
				}

			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> board[i][j];
			if (board[i][j] == 2)
			{
				board[i][j] = 1;
				start_y = i;
				start_x = j;
			}
			else if (board[i][j] == 3)
			{
				board[i][j] = 1;
				end_y = i;
				end_x = j;
			}
		}
	}

	BFS();

	cout << min1;

	return 0;
}