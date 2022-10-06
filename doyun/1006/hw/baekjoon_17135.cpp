#include <iostream>
#include <queue>

using namespace std;

// 백준 17135 - 캐슬 디펜스
// 골드 3

// bfs
// sliding window

int board_origin[31][16];
int board[31][16]; // 15열부터 ~ (15 + n - 1)열 : sliding window
int chk[31][16];

// 궁수는 항상 3명
// for문 3개 돌려서 궁수 배치 (궁수는 무조건 n + 1 행에)
// BFS 돌려서 몇명 죽일 수 있는지 확인
// n만큼 궁수들 1만큼 올려서 확인하면 됨(최대 15)
// 같은 거리의 적이 여럿일 경우 -> 가장 왼쪽 -> pq 사용

// 반례 : *동시에* 세 궁수가 적을 없애야 한다
// 미리미리 없애면 궁수가 같은 적 없애는 경우 생기지 않음 
// 문제에는 같은 적 없애는 경우 포함

int n, m, d;
int tmp_cnt; // 현재
int max1 = 0; // 최대값
int x_mov[] = { -1, 1, 0, 0 };
int y_mov[] = { 0, 0, -1, 1 };

struct archer
{
	int y = -1;
	int x = -1;
	int dist;
};

archer arc_arr[3]; // 궁수 세명
archer goal[3]; // 매턴 동시에 없애야 하는 애들 셋

void chkClear()
{
	for (int i = 0; i < 31; i++)
	{
		for (int j = 0; j < m; j++) chk[i][j] = 0;
	}
}

void copyBoard()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			board[i + 15][j] = board_origin[i + 15][j];
		}
	}
}

int now_y_start, now_y_end; // 현재 이동한 열 값
// BFS -> 궁수가 이동

bool operator<(archer a1, archer a2)
{
	if (a1.dist > a2.dist) return true;
	else if (a1.dist == a2.dist && a1.x > a2.x) return true;
	return false;
}

priority_queue<archer> pq;

void BFS(int start_y, int start_x, int idx)
{
	chkClear();
	while (!pq.empty()) pq.pop();

	chk[start_y][start_x] = 1;
	pq.push({ start_y, start_x, 0 });

	while (!pq.empty())
	{
		archer tmp = pq.top();
		pq.pop();
		if (board[tmp.y][tmp.x] == 1)
		{
			//board[tmp.y][tmp.x] = 0;
			//tmp_cnt++;
			goal[idx].y = tmp.y;
			goal[idx].x = tmp.x;
			return;
		}

		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= now_y_start && tmp.y + y_mov[i] < now_y_end &&
				tmp.x + x_mov[i] >= 0 && tmp.x + x_mov[i] < m &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0 && 
				tmp.dist < d)
			{
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] = 1;
				pq.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.dist + 1 });
			}
		}
	}
}


int main()
{
	cin >> n >> m >> d;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> board_origin[i + 15][j];
		}
	}

	// 궁수 세명 for문 세개로 지정 후
	// 궁수 위치를 차례로 위로 올려가며 tmp 값 변경
	// tmp 값과 max 값 비교
	
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			for (int r = j + 1; r < m; r++)
			{
				arc_arr[0].y = 15 + n;
				arc_arr[1].y = 15 + n;
				arc_arr[2].y = 15 + n;

				arc_arr[0].x = i;
				arc_arr[1].x = j;
				arc_arr[2].x = r;

				tmp_cnt = 0;

				copyBoard();
				//chkClear();
				now_y_start = 15;
				now_y_end = 15 + n;

				goal[0].y = -1;
				goal[0].x = -1;
				goal[1].y = -1;
				goal[1].x = -1;
				goal[2].y = -1;
				goal[2].x = -1;


				for (int k = 0; k < n; k++)
				{
					for (int r = 0; r < 3; r++)
					{
						BFS(arc_arr[r].y, arc_arr[r].x, r);
					}

					// 동시에 없애기
					// 만약 y와 x -1이라면 pass
					// 이미 없어졌다면 pass
					for (int r = 0; r < 3; r++)
					{
						if (goal[r].y == -1 && goal[r].x == -1) continue;
						if (board[goal[r].y][goal[r].x] == 1)
						{
							board[goal[r].y][goal[r].x] = 0;
							tmp_cnt++;
						}
					}

					now_y_start--;
					now_y_end--;
					arc_arr[0].y--;
					arc_arr[1].y--;
					arc_arr[2].y--;
				}
				if (max1 < tmp_cnt) max1 = tmp_cnt;
			}
		}
	}


	cout << max1;
	
	return 0;
}