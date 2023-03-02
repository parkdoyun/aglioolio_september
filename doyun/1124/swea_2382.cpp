#include <iostream>
#include <queue>

using namespace std;

// swea 2382 - 미생물 격리
// BFS

// 시간 갱신될 때마다 다시 pq에 담기
// 보드에 기록

struct node
{
	int y;
	int x;
	int n;
	int dir;
	int time = 0;
};
struct node2
{
	int n;
	int dir;
	int time = 0;
};

int n, m, k;
node2 board[102][102];
int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };

bool operator<(node n1, node n2)
{
	if (n1.time > n2.time) return true;
	if (n1.time == n2.time && n1.n > n2.n) return true;
	return false;
}

priority_queue<node> pq;
void boardClr()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (board[i][j].n == 0) continue;
			pq.push({ i, j, board[i][j].n, board[i][j].dir, board[i][j].time });
			board[i][j].n = 0;
		}
	}
}

void BFS()
{
	int now_time = 0;
	while (!pq.empty())
	{
		node tmp = pq.top();
		if (now_time == m) break;
		pq.pop();

		tmp.y += y_mov[tmp.dir];
		tmp.x += x_mov[tmp.dir];

		if (tmp.y == 0 || tmp.y == n - 1 ||
			tmp.x == 0 || tmp.x == n - 1)
		{
			tmp.n /= 2;
			if (tmp.dir == 0 || tmp.dir == 2) tmp.dir++;
			else tmp.dir--;
		}

		board[tmp.y][tmp.x].n += tmp.n;
		board[tmp.y][tmp.x].dir = tmp.dir;
		board[tmp.y][tmp.x].time = tmp.time;

		if (pq.empty())
		{
			// 다 채우기
			now_time++;
			boardClr();
		}

	}
}

int main()
{
	int T, y, x, num, dir;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> n >> m >> k;
		while (!pq.empty()) pq.pop();

		for (int i = 0; i < k; i++)
		{
			cin >> y >> x >> num >> dir;
			dir--;
			pq.push({ y, x, num, dir , 0 });
		}

		BFS();

		int res = 0;
		while (!pq.empty())
		{
			node tmp = pq.top();
			pq.pop();
			res += tmp.n;
		}

		cout << '#' << tc << ' ' << res << '\n';
	}

	return 0;
}