#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 코드트리 - 예술성
// simulation
// 골드 3

// grp_edge는 나중에 돌아가면서
// 십자 회전 좀 이상함

int n;
int board[30][30];
int board_cp[16][16]; // 회전용 배열
int visit[30][30];
int grp_chk[30][30]; // 이미 그룹 선택됨
vector<vector<int>> grp_edge;
int total_score = 0; // 예술 점수

struct grp // group
{
	int num; // 칸의 숫자
	int size; // 칸 개수
	int sy; // 시작하는 좌표
	int sx; 
};
vector<grp> grp_info;

void square_rotate(int sy, int sx, int size) // 작은 사각형 회전
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board_cp[i][j] = board[sy + i][sx + j];
		}
	}

	// 다시 집어넣기
	int y1, x1;
	x1 = 0;
	for (int i = 0; i < size; i++)
	{
		y1 = size - 1;
		for (int j = 0; j < size; j++)
		{
			board[sy + i][sx + j] = board_cp[y1][x1];
			y1--;
		}
		x1++;
	}
}
int rotate_path[16];
void rotate()
{
	// 십자 회전 (반시계)
	int cy = n / 2; // 중심 좌표
	int cx = n / 2;
	int idx = 0;
	for (int i = cx - 1; i >= 0; i--)
	{
		rotate_path[idx] = board[cy][i];
		idx++;
		board[cy][i] = board[cy - idx][cx];
	}
	idx = 1;
	for (int i = cy - 1; i >= 0; i--)
	{
		board[i][cx] = board[cy][cx + idx];
		idx++;
	}
	idx = 0;
	for (int i = cx + 1; i < n; i++)
	{
		board[cy][i] = board[i][cx];
		board[i][cx] = rotate_path[idx];
		idx++;
	}
	
	// 각 네 귀퉁이 회전
	int ty[4] = { 0, 0, cy + 1, cy + 1 };
	int tx[4] = { 0, cx + 1, 0, cx + 1 };

	for (int i = 0; i < 4; i++)
	{
		square_rotate(ty[i], tx[i], n / 2);
	}
}
int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };


// 맞닿아 있는 애들도 visit 처리 필요
int tmp_cnt;
void makeGrp(int y, int x, int num, int idx) // 그룹 생성하기
{
	visit[y][x] = 1;
	grp_chk[y][x] = idx;
	tmp_cnt++;

	int ty, tx;
	for (int i = 0; i < 4; i++)
	{
		ty = y + y_mov[i];
		tx = x + x_mov[i];

		if (ty >= 0 && ty < n && tx >= 0 && tx < n && visit[ty][tx] == 0 && board[ty][tx] == num)
		{
			makeGrp(ty, tx, num, idx);
		}
	}
}
void calBorder(int sy, int sx, int num, int grp_n) // 각 그룹 경계선 얼만지 계산
{
	visit[sy][sx] = 1;
	int ty, tx;
	for (int i = 0; i < 4; i++)
	{
		ty = sy + y_mov[i];
		tx = sx + x_mov[i];
		if(ty >= 0 && ty < n&& tx >= 0 && tx < n)
		{
			if (visit[ty][tx] == 0 && board[ty][tx] == num && grp_chk[ty][tx] == grp_n)
			{
				calBorder(ty, tx, num, grp_n);
			}
			else if (grp_chk[ty][tx] != grp_n) // 다른 곳
			{
				grp_edge[grp_n][grp_chk[ty][tx]]++;
			}
		}
	}
}

void visitClr()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) visit[i][j] = 0;
	}
}

void totalClr()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			visit[i][j] = 0;
			grp_chk[i][j] = 0;
		}
	}
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
		}
	}

	for (int tc = 0; tc <= 3; tc++)
	{
		// 초기화
		totalClr();

		grp_info.resize(1); // 0번 인덱스 사용 X

		// 그룹 생성하기
		int idx = 1;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (visit[i][j] == 0)
				{
					tmp_cnt = 0;
					makeGrp(i, j, board[i][j], idx);
					idx++;
					grp_info.push_back({ board[i][j], tmp_cnt, i, j });
				}
			}
		}
		grp_edge.resize(idx);

		// 맞닿아 있는 애들 구하기(grp_edge)
		visitClr();
		for (int i = 1; i < idx; i++)
		{
			grp_edge[i].resize(idx);
			for (int j = 1; j < idx; j++) grp_edge[i][j] = 0; // 초기화
			calBorder(grp_info[i].sy, grp_info[i].sx, grp_info[i].num, i);
		}

		// 0 이상인 애들 다 구하기
		for (int i = 1; i < idx - 1; i++)
		{
			for (int j = i + 1; j < idx; j++)
			{
				if (grp_edge[i][j] > 0) total_score += (grp_info[i].size + grp_info[j].size) * grp_edge[i][j] * grp_info[i].num * grp_info[j].num;
			}
		}

		// 회전
		rotate();
	}

	cout << total_score;

	return 0;
}