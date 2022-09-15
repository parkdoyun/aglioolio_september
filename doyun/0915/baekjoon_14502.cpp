#include <iostream>
#include <queue>

using namespace std;

// 백준 14502 - 연구소
// 브루트포스, bfs
// 골드 4

// 벽 반드시 3개 세워야 함
// 빈칸은 반드시 0만 체크
// bfs
// 벽 세개 세운 모든 가짓수 다 해보기 -> 8*8이라 시간초과는 안 날듯

int board[9][9]; // 원본 지도
int tmp_board[9][9]; // 시뮬레이션하는 지도
int chk[9][9];
int n, m;

int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };

struct node
{
	int y;
	int x;
};

queue<node> q_origin; // 원래 초기 2만 담긴 큐
queue<node> q;

void chkClear() // chk 지우고 시험 지도 복구
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			chk[i][j] = 0;
			tmp_board[i][j] = board[i][j];
		}
	}
}

int BFS()
{
	int pollu_n = 0; // 오염되는 곳
	//while (!q.empty()) q.pop();

	while (!q.empty())
	{
		node tmp = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 0 && tmp.y + y_mov[i] < n &&
				tmp.x + x_mov[i] >= 0 && tmp.x + x_mov[i] < m &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0 &&
				tmp_board[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0)
			{
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] = 1;
				tmp_board[tmp.y + y_mov[i]][tmp.x + x_mov[i]] = 2;
				q.push({ tmp.y + y_mov[i], tmp.x + x_mov[i] });
				pollu_n++;
			}
		}
	}
	return pollu_n;
}

int main()
{
	int wall_cnt = 0; // 벽 개수
	int p_n = 0; // 원래 오염된 곳 개수

	cin >> n >> m;

	// 0인 부분 다 넣어놓기
	vector<node> zero_vec;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> board[i][j];
			if (board[i][j] == 1) wall_cnt++;
			else if (board[i][j] == 2)
			{
				// q에 push 미리 해야 함
				q_origin.push({ i, j });
				p_n++;
			}
			else
			{
				zero_vec.push_back({ i, j });
			}
		}
	}


	// 벽 3개 임의로 세워놓고 최댓값 만들기
	// for문 3개?
	int max = -1;
	for (int i = 0; i < zero_vec.size(); i++)
	{
		for (int j = i + 1; j < zero_vec.size(); j++)
		{
			for (int r = j + 1; r < zero_vec.size(); r++)
			{
				q = q_origin;
				chkClear();

				// 벽 3개 세우고
				tmp_board[zero_vec[i].y][zero_vec[i].x] = 1;
				tmp_board[zero_vec[j].y][zero_vec[j].x] = 1;
				tmp_board[zero_vec[r].y][zero_vec[r].x] = 1;

				int res = BFS();
				int tmp = n * m - res - wall_cnt - p_n;
				if (tmp > max) max = tmp;
				
			}
		}
	}

	cout << max - 3;

	return 0;
}