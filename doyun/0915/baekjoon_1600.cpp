#include <iostream>
#include <queue>

using namespace std;

// 백준 1600 - 말이 되고픈 원숭이
// bfs
// 골드 3

// 총 말 움직임 횟수 (8) + 인접 (4) bfs 돌리면 될 듯 
// 도착하면 최솟값 비교
// 만약 도착 X, q.empty() -> -1 출력

// 더 빨리 가도 나중에 말처럼 가야 하는 경우 발생
// 마지막만 말처럼 점프해야 하는 게 아니면? => 해결해야 함
// 해결책 : 3차원 배열로 chk 배열을 생성하여 말 움직임 갯수에 따라 아예 chk 따로 구분
// chk 배열 3차원? [31][201][201]
// k에 따라 다르게 해보자

struct node
{
	int y;
	int x;
	int cnt = 0;
	int horse_cnt = 0;
};

int board[201][201];
int chk[31][201][201];

queue<node> q;
int k, w, h;

int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };
int horse_y_mov[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int horse_x_mov[] = { -1, -2, -2, -1, 1, 2, 2, 1 };

int BFS()
{
	int min = 1000000000;
	int min_chk = -1;

	while (!q.empty())
	{
		node tmp = q.front();
		q.pop();

		//cout << tmp.y << ',' << tmp.x << ' ' << tmp.horse_cnt << endl;

		if (tmp.y == h - 1 && tmp.x == w - 1)
		{
			min_chk = 0;
			if (min > tmp.cnt) min = tmp.cnt;
			continue;
		}

		if (tmp.horse_cnt < k)
		{
			// horse 이동
			for (int i = 0; i < 8; i++)
			{
				if (tmp.y + horse_y_mov[i] >= 0 && tmp.y + horse_y_mov[i] < h &&
					tmp.x + horse_x_mov[i] >= 0 && tmp.x + horse_x_mov[i] < w &&
					chk[tmp.horse_cnt + 1][tmp.y + horse_y_mov[i]][tmp.x + horse_x_mov[i]] == 0 &&
					board[tmp.y + horse_y_mov[i]][tmp.x + horse_x_mov[i]] == 0)
				{
					chk[tmp.horse_cnt + 1][tmp.y + horse_y_mov[i]][tmp.x + horse_x_mov[i]] = 1;
					q.push({ tmp.y + horse_y_mov[i], tmp.x + horse_x_mov[i], tmp.cnt + 1, tmp.horse_cnt + 1 });
				}
			}
		}
		// 인접 이동
		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 0 && tmp.y + y_mov[i] < h &&
				tmp.x + x_mov[i] >= 0 && tmp.x + x_mov[i] < w &&
				chk[tmp.horse_cnt][tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0 &&
				board[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0)
			{
				chk[tmp.horse_cnt][tmp.y + y_mov[i]][tmp.x + x_mov[i]] = 1;
				q.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.cnt + 1 , tmp.horse_cnt });
			}
		}


	}

	if (min_chk == -1) return -1;
	return min;
}

int main()
{
	cin >> k >> w >> h;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			cin >> board[i][j];
		}
	}


	chk[0][0][0] = 1;
	q.push({ 0, 0, 0, 0 });
	cout << BFS();

	return 0;
}