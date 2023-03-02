#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// softeer 인증평가 2차 - garage game
// backtracking, 시뮬레이션
// 별 3
// 미완

// 해당 면적 선택했을 때 -> 1번으로 취급
// 3번 해서 최댓값 출력
// visit 체크해서 안 한 곳만 하기

int n;
long long int board[16][16];
int visit[3][16][16];
long long int board_spare[32][16]; // 차고
long long int maxScore = 0;
int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };
struct node
{
	int y;
	int x;
};
queue<node> q;
long long int tmp_arr[32];

void backtracking(int lv, long long int tmp_score, vector<vector<long long int>> vec, vector<vector<long long int>> garage)
{
	if (lv == 3)
	{
		// 점수 계산
		if (tmp_score > maxScore) maxScore = tmp_score;
		return;
	}
	
	// 초기화
	vector<vector<long long int>> new_vec;
	vector<vector<long long int>> new_garage;
	new_garage.resize(n * 2);
	new_vec.resize(n);
	for (int i = 0; i < n; i++)
	{
		new_vec[i].resize(n);
		new_garage[i].resize(n);
		for (int j = 0; j < n; j++) visit[lv][i][j] = 0;
	}
	for (int i = n; i < n * 2; i++) new_garage[i].resize(n);
	
	long long int tmp_s, cnt;
	int ty, tx, max_y, max_x, min_y, min_x;
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (vec[i][j] == -1) continue; // 아무 차도 없는 경우
			if (visit[lv][i][j] != 0) continue; // 이미 테스트 한 경우
			// i, j랑 같은 애들 빼고 직사각형 계산 후 자리 채우기
			max_y = -1; max_x = -1;
			min_y = n; min_x = n;
			while (!q.empty()) q.pop();
			for (int r = 0; r < n; r++)
			{
				for (int k = 0; k < n; k++)
				{
					new_vec[r][k] = vec[r][k];
					new_garage[r][k] = garage[r][k];
				}
			}
			for (int r = n; r < n * 2; r++)
			{
				for (int k = 0; k < n; k++)
				{
					new_garage[r][k] = garage[r][k];
				}
			}

			cnt = 0;
			q.push({ i, j });
			tmp_s = vec[i][j];
			while (!q.empty())
			{
				node tmp = q.front();
				q.pop();

				if (visit[lv][tmp.y][tmp.x] == 1) continue;
				visit[lv][tmp.y][tmp.x] = 1;
				new_vec[tmp.y][tmp.x] = -1;
				if (max_x < tmp.x) max_x = tmp.x; if (max_y < tmp.y) max_y = tmp.y;
				if (min_x > tmp.x) min_x = tmp.x; if (min_y > tmp.y) min_y = tmp.y;
				cnt++;

				for (int i = 0; i < 4; i++)
				{
					ty = tmp.y + y_mov[i];
					tx = tmp.x + x_mov[i];
					if (ty >= 0 && ty < n && tx >= 0 && tx < n &&
						new_vec[ty][tx] == tmp_s && visit[lv][ty][tx] == 0)
					{
						q.push({ ty, tx });
					}
				}
			}

			// 차고에 있는 차들로 채우기
			for (int i = 0; i < n; i++)
			{
				// tmp_arr로 옮긴 후 다시 옮기기
				int tmp_idx = n * 2 - 1;
				for (int j = 0; j < n; j++)
				{
					if (new_vec[j][i] == -1)
					{
						new_vec[j][i] = new_garage[tmp_idx][i];
						new_garage[tmp_idx][i] = -1;
						tmp_idx--;
					}
				}
				// new_garage 땡기기
				tmp_idx = n * 2 - 1;
				for (int j = 0; j < n * 2; j++) tmp_arr[j] = -1;
				for (int j = 0; j < n * 2; j++)
				{
					if (new_garage[j][i] == -1) continue;
					tmp_arr[tmp_idx] = new_garage[j][i];
					tmp_idx--;
				}
				// 채우기
				for (int j = 0; j < n * 2; j++) new_garage[j][i] = tmp_arr[j];
			}

			// 직사각형 계산
			// 다음 backtracking
			backtracking(lv + 1, tmp_score + cnt + (long long int)((max_y - min_y + 1) * (max_x - min_x + 1)), new_vec, new_garage);
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;

	vector<vector<long long int>> new_vec;
	vector<vector<long long int>> new_garage;
	new_vec.resize(n);
	new_garage.resize(n * 2);

	for (int i = 0; i < n * 2; i++)
	{
		new_garage[i].resize(n);
		for (int j = 0; j < n; j++)
		{
			cin >> board_spare[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		new_vec[i].resize(n);
		for (int j = 0; j < n; j++)
		{
			cin >> board[i][j];
		}
	}

	for (int r = 0; r < n; r++)
	{
		for (int k = 0; k < n; k++)
		{
			new_vec[r][k] = board[r][k];
			new_garage[r][k] = board_spare[r][k];
		}
	}
	for (int r = n; r < n * 2; r++)
	{
		for (int k = 0; k < n; k++)
		{
			new_garage[r][k] = board_spare[r][k];
		}
	}

	// backtracking

	backtracking(0, 0, new_vec, new_garage);

	cout << maxScore;
	

	return 0;
}