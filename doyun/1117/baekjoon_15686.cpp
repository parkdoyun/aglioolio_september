#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 백준 15686 - 치킨 배달
// dfs, exhaustive search
// 골드 5

// m개 각각 고르고 치킨 거리 비교 -> 가장 작은 치킨 거리 출력
// backtracking으로 최대 m개 고르기 (m개가 아닐 수도 있다)
// 각각 집부터 치킨 거리 -> BFS => 시간초과 => for문 2개 돌려서 계산

int n, m;
int board[51][51];
int path[14];
int min1 = 1000000000;

struct h
{
	int y;
	int x;
	int d;
};

vector<h> house; // 집
vector<h> chicken; // 치킨 집


int tmp;

void cal2()
{
	tmp = 0;
	for (int i = 0; i < house.size(); i++)
	{
		int tmp_y = house[i].y;
		int tmp_x = house[i].x;

		int tmp_min = 100000000000;
		int tmp_now;
		for (int j = 0; j < chicken.size(); j++)
		{
			if (path[j] == 0) continue;
			tmp_now = abs(chicken[j].y - tmp_y) + abs(chicken[j].x - tmp_x);
			if (tmp_now < tmp_min) tmp_min = tmp_now;
		}
		tmp += tmp_min;
	}
}


void backtracking(int lv, int cnt)
{
	if (lv == chicken.size())
	{
		if (cnt == 0) return; // 전부 폐업시켜버리면

		// 치킨 거리 계산
		cal2();
		if (tmp < min1) min1 = tmp;
		return;
	}

	if (cnt != m)
	{
		path[lv] = 1;
		backtracking(lv + 1, cnt + 1);
		path[lv] = 0;
		backtracking(lv + 1, cnt);
	}
	else
	{
		path[lv] = 0;
		backtracking(lv + 1, cnt);
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> board[i][j];
			if (board[i][j] == 1)
			{
				house.push_back({ i, j });
			}
			else if (board[i][j] == 2)
			{
				chicken.push_back({ i, j });
			}
		}
	}

	path[0] = 0;
	backtracking(1, 0);
	path[0] = 1;
	backtracking(1, 1);

	cout << min1;


	return 0;
}