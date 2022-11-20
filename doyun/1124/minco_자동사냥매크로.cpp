#include <iostream>
#include <queue>
using namespace std;

// 민코딩 - 자동사냥 매크로
// BFS

int n;
int board[21][21];
int chk[21][21];
int lv = 2;
int exp1 = 0; // 경험치
int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };
int now_y, now_x;

void chkClear()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) chk[i][j] = 0;
	}
}

struct node
{
	int y;
	int x;
	int dist;
};

bool operator<(node n1, node n2)
{
	if (n1.dist > n2.dist) return true;
	else if (n1.dist == n2.dist && n1.y > n2.y) return true;
	else if (n1.dist == n2.dist && n1.y == n2.y && n1.x > n2.x) return true;
	return false;
}

priority_queue<node> pq;
void BFS(int y, int x, int &y1, int &x1, int &dist) // 다음 이동할 곳 구함
{
	// 사냥할 곳 구하면 바로 나감
	while (!pq.empty()) pq.pop();
	chkClear();
	
	pq.push({ y, x, 0 });

	while (!pq.empty())
	{
		node tmp = pq.top();
		pq.pop();

		if (chk[tmp.y][tmp.x] == 1) continue;
		chk[tmp.y][tmp.x] = 1;

		if (board[tmp.y][tmp.x] > 0 && board[tmp.y][tmp.x] < lv)
		{
			y1 = tmp.y;
			x1 = tmp.x;
			dist = tmp.dist;
			return;
		}

		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 0 && tmp.y + y_mov[i] < n &&
				tmp.x + x_mov[i] >= 0 && tmp.x + x_mov[i] < n &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0 &&
				board[tmp.y + y_mov[i]][tmp.x + x_mov[i]] <= lv)
			{
				pq.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.dist + 1 });
			}
		}
	}

	y1 = -1;
	x1 = -1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);


	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> board[i][j];
			if (board[i][j] == 9)
			{
				board[i][j] = 0;
				now_y = i;
				now_x = j;
			}
		}
	}

	int end_y, end_x, end_d;
	int time = 0;
	while (true)
	{
		BFS(now_y, now_x, end_y, end_x, end_d);
		if (end_y == -1 && end_x == -1) break;
		now_y = end_y;
		now_x = end_x;
		time += end_d;
		exp1++;
		if (exp1 == lv)
		{
			lv++;
			exp1 = 0;
		}
		board[now_y][now_x] = 0;
	}

	cout << time;

	return 0;
}