#include <iostream>
#include <vector>

using namespace std;

// 민코딩 greedy의 탑 - 전구 켜기
// greedy, backtracking

// 버튼 1번 누르나 2번 누르나 동일
// 최소 구하므로 -> 누를지 말지만 세면 됨
// backtracking으로 가짓수 구하기

int n, m, k;
int path[19];
int light[11];
int button[19][9];
int min1 = 1000000000;

int cal() // 전구 계산
{
	int res = 0;
	int btn_cnt = 0;
	for (int i = 0; i < m; i++)
	{
		if (path[i] == 0) continue;
		btn_cnt++;
		for (int j = 0; j < k; j++)
		{
			if (light[button[i][j]] == 1) light[button[i][j]] = 0;
			else light[button[i][j]] = 1;
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (light[i] == 0) res++;
	}
	for (int i = 0; i < m; i++)
	{
		if (path[i] == 0) continue;
		for (int j = 0; j < k; j++)
		{
			if (light[button[i][j]] == 1) light[button[i][j]] = 0;
			else light[button[i][j]] = 1;
		}
	}
	if (res == 0)
	{
		return btn_cnt;
	}
	return -1;
}

void backtracking(int lv)
{
	if (lv == m)
	{
		// 전구 계산
		int tmp_cnt = cal();
		if (tmp_cnt != -1)
		{
			if (tmp_cnt < min1) min1 = tmp_cnt;
		}
		return;
	}

	path[lv] = 0;
	backtracking(lv + 1);
	path[lv] = 1;
	backtracking(lv + 1);
}

int main()
{
	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++)
	{
		cin >> light[i];
	}

	int a;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < k; j++)
		{
			cin >> button[i][j];
		}
	}

	path[0] = 0;
	backtracking(1);
	path[0] = 1;
	backtracking(1);


	if (min1 == 1000000000) min1 = -1;
	cout << min1;


	return 0;
}