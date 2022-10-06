#include <iostream>
#include <queue>

using namespace std;

// swea 5656 - 벽돌 깨기
// 모든 경우의 수 다 해보고 제일 많이 깬 것 출력
// 경우의 수 => DFS, backtracking
// 연쇄적으로 터지기 -> BFS 이용

// 3차 배열로 생성 -> 많아야 4단계 저장 가능
int board[16][13];
int board_cp[5][16][13]; // 이걸로 시뮬레이션 사용
int n, w, h;
int max1; // n단계 후 가장 적게 남은 최종 벽돌 수

// 깨뜨리고 복원 함수
// 동시에 제거되고 -> 나중에 다 밑으로 내리기
// 깨뜨린 벽돌 수 반환
struct brick
{
	int y;
	int x;
	int size; // 길이
};
queue<brick> q;

int startH(int x, int lv) // 이 위치에서 떨어뜨리면 구슬 어디에서 터지는지?
{
	int res_y = -1;
	for (int i = 0; i < h; i++)
	{
		if (board_cp[lv][i][x] != 0)
		{
			res_y = i;
			break;
		}
	}

	return res_y;
}

int removeBricks(int start_x, int start_y, int lv)
{
	int res = 0;

	// 이전 단계의 벽돌 모양 가져옴
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++) board_cp[lv][i][j] = board_cp[lv - 1][i][j];
	}

	// 깨뜨리기 (bfs)
	// 초기화
	while (!q.empty()) q.pop();
	q.push({ start_y, start_x, board_cp[lv][start_y][start_x] });
	res = 1;
	
	while (!q.empty())
	{
		brick tmp = q.front();
		q.pop();

		board_cp[lv][tmp.y][tmp.x] = 0;

		// 상하좌우 확인
		for (int i = 1; i < tmp.size; i++)
		{
			// 하
			if (tmp.y + i < h && board_cp[lv][tmp.y + i][tmp.x] != 0)
			{
				res++;
				if (board_cp[lv][tmp.y + i][tmp.x] == 1)
				{
					board_cp[lv][tmp.y + i][tmp.x] = 0;
				}
				else q.push({ tmp.y + i, tmp.x, board_cp[lv][tmp.y + i][tmp.x] });
			}
			// 상
			if (tmp.y - i >= 0 && board_cp[lv][tmp.y - i][tmp.x] != 0)
			{
				res++;
				if (board_cp[lv][tmp.y - i][tmp.x] == 1)
				{
					board_cp[lv][tmp.y - i][tmp.x] = 0;
				}
				else q.push({ tmp.y - i, tmp.x, board_cp[lv][tmp.y - i][tmp.x] });
			}
			// 우
			if (tmp.x + i < w && board_cp[lv][tmp.y][tmp.x + i] != 0)
			{
				res++;
				if (board_cp[lv][tmp.y][tmp.x + i] == 1)
				{
					board_cp[lv][tmp.y][tmp.x + i] = 0;
				}
				else q.push({ tmp.y, tmp.x + i, board_cp[lv][tmp.y][tmp.x + i] });
			}
			// 좌
			if (tmp.x - i >= 0 && board_cp[lv][tmp.y][tmp.x - i] != 0)
			{
				res++;
				if (board_cp[lv][tmp.y][tmp.x - i] == 1)
				{
					board_cp[lv][tmp.y][tmp.x - i] = 0;
				}
				else q.push({ tmp.y, tmp.x - i, board_cp[lv][tmp.y][tmp.x - i] });
			}
		}
	}


	// 밑으로 내리기
	for (int i = 0; i < w; i++)
	{
		int arr_h[16] = { 0 };
		int idx = 0;
		for (int j = 0; j < h; j++)
		{
			if (board_cp[lv][j][i] != 0)
			{
				arr_h[idx] = board_cp[lv][j][i];
				idx++;
				board_cp[lv][j][i] = 0;
			}
		}

		// 다시 넣기
		int k = 0;
		for (int j = h - idx; j < h; j++)
		{
			board_cp[lv][j][i] = arr_h[k];
			k++;
		}
	}

	return res;
}

void DFS(int lv)
{
	if (lv == n + 1)
	{
		// 여기서 check
		int res = 0;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (board_cp[n][i][j] != 0) res++;
			}
		}
		if (max1 > res) max1 = res;
		return;
	}

	for (int i = 0; i < w; i++)
	{
		int start_y = startH(i, lv - 1);
		if (start_y == -1) continue;
		// 깨뜨리기
		removeBricks(i, start_y, lv);
		
		DFS(lv + 1);
	}
}

int main()
{
	int T;
	cin >> T;
	
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> n >> w >> h;
		max1 = 10000; // 가장 많이 깬 것
		int total_cnt = 0;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				cin >> board[i][j];
				board_cp[0][i][j] = board[i][j];
				if (board[i][j] != 0) total_cnt++;
			}
		}

		for (int i = 0; i < w; i++)
		{
			
			int start_y = startH(i, 0);

			if (start_y == -1) continue;

			// 깨뜨리기
			removeBricks(i, start_y, 1);

			// DFS
			DFS(2);
		}

		if (max1 == 10000) max1 = 0; // 아무것도 깨뜨린 게 없다면
		cout << '#' << tc << ' ' << max1 << '\n';
	}

	return 0;
}