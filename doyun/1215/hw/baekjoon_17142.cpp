#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 백준 17142 - 연구소 3
// brute-force
// 골드 3

// m개 활성 상태로 변경 -> backtracking 이용해서 조합
// 활성 상태면 3으로 변경

// 시간 초과 => vector.size() 연산 속도 때문 => 변수로 고정하니 통과
// string, vector 연산은 오래 걸림!!

int n, m;
int board[51][51];
int board_cp[51][51];
int chk[51][51];
int path[11];
int min1 = 10000000;
int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };
int vec_g_size;

struct germ
{
	int y;
	int x;
	int time = 0;
};
bool operator<(germ g1, germ g2)
{
	if (g1.time > g2.time) return true;
	return false;
}

vector<germ> vec_g;

void copy()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			board_cp[i][j] = board[i][j];
			chk[i][j] = 0;
		}
	}
}

int board_chk()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			if (board_cp[i][j] == 0) return -1;
		}
	}
	return 0;
}

priority_queue<germ> pq;
int BFS()
{
	while (!pq.empty()) pq.pop();

	for (int i = 0; i < vec_g_size; i++)
	{		
		if (path[i] == 0) continue;
		pq.push({ vec_g[i].y, vec_g[i].x, 0 });
	}

	int total_time = 0;
	if (board_chk() == 0) return 0;
	while (!pq.empty())
	{
		germ tmp = pq.top();
		pq.pop();

		if (chk[tmp.y][tmp.x] == 1) continue;
		chk[tmp.y][tmp.x] = 1;
		if (board_chk() == 0)
		{
			total_time++;
			break;
		}

		int flag = 0;
		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 0 && tmp.y + y_mov[i] < n &&
				tmp.x + x_mov[i] >= 0 && tmp.x + x_mov[i] < n &&
				board_cp[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0 &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] != 1)
			{
				flag = 1;
				board_cp[tmp.y + y_mov[i]][tmp.x + x_mov[i]] = 3;
				pq.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.time + 1 });
			}
			else if (tmp.y + y_mov[i] >= 0 && tmp.y + y_mov[i] < n &&
				tmp.x + x_mov[i] >= 0 && tmp.x + x_mov[i] < n &&
				board_cp[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 2 &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] != 1)
			{
				flag = 1;
				pq.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.time + 1 });
			}
		}

		// 만약 이미 바이러스인데 아무곳도 감염시키지 않았다면 그냥 놔두는 게 더 빠른 길

		if (board_cp[tmp.y][tmp.x] == 2 && flag == 0) continue;
		if (tmp.time > total_time) total_time = tmp.time;
	}
	return total_time;
}

int cal()
{
	int res = BFS();

	// 전부 확인됐는지 확인
	if (board_chk() == -1) return -1;

	return res;
}

void backtracking(int lv, int prev)
{
	if (lv == m)
	{
		// 시간 계산
		copy();
		int res = cal();
		if (res != -1 && res < min1) min1 = res;
		return;
	}

	for (int i = prev + 1; i < vec_g_size; i++)
	{
		path[i] = 1;
		backtracking(lv + 1, i);
		path[i] = 0;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> board[i][j];
			if (board[i][j] == 2)
			{
				vec_g.push_back({ i, j });
			}
		}
	}
	vec_g_size = vec_g.size();

	for (int i = 0; i < vec_g_size; i++)
	{
		path[i] = 1;
		backtracking(1, i);
		path[i] = 0;
	}

	if (min1 == 10000000) cout << -1;
	else cout << min1;

	return 0;
}