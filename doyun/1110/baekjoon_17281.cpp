#include <iostream>
#include <vector>

using namespace std;

// 백준 17281 - 야구공
// 골드 4
// DFS, backtracking

// 모든 경우의 수 다 하고 최대점수 출력
// backtracking 사용
// 1번 선수는 무조건 4번

int n;
int path[10];
int checked[10];

vector<vector<int>> vec; // 득점 결과
int max1 = 0;

int base[3] = { -1, -1, -1 };

int cal() // 득점 계산 함수
{
	int res = 0;
	int out;
	int now_player = 1;
	base[2] = -1;
	base[1] = -1;
	base[0] = -1;


	for (int i = 1; i <= n; i++)
	{
		out = 0;
		base[2] = -1;
		base[1] = -1;
		base[0] = -1;

		while (out < 3)
		{
			if (vec[i][path[now_player]] == 0) // 아웃
			{
				out++;
			}
			else if (vec[i][path[now_player]] == 1) // 안타 (1루타)
			{
				if (base[2] != -1)
				{
					res++;
				}
				// 1루씩 당기기
				for (int i = 2; i >= 1; i--)
				{
					base[i] = base[i - 1];
				}
				base[0] = 1;
			}
			else if (vec[i][path[now_player]] == 2) // 2루타
			{
				if (base[2] != -1)
				{
					res++;
				}
				if (base[1] != -1)
				{
					res++;
				}
				base[2] = base[0];
				base[1] = 1;
				base[0] = -1;
				
			}
			else if (vec[i][path[now_player]] == 3) // 3루타
			{
				if (base[2] != -1)
				{
					res++;
				}
				if (base[1] != -1)
				{
					res++;
				}
				if (base[0] != -1)
				{
					res++;
				}
				base[2] = 1;
				base[1] = -1;
				base[0] = -1;
			}
			else // 홈런
			{
				if (base[2] != -1)
				{
					res++;
				}
				if (base[1] != -1)
				{
					res++;
				}
				if (base[0] != -1)
				{
					res++;
				}
				res++;
				base[2] = -1;
				base[1] = -1;
				base[0] = -1;
			}
			now_player++;
			if (now_player == 10) now_player = 1;
		}

	}

	return res;
}

void DFS(int lv)
{
	if (lv == 4) // pass
	{
		DFS(lv + 1);
		return;
	}
	if (lv == 10)
	{
		// 득점 계산
		int tmp = cal();
		if (tmp > max1) max1 = tmp;
		return;
	}

	for (int i = 2; i <= 9; i++)
	{
		if (checked[i] == 0)
		{
			checked[i] = 1;
			path[lv] = i;
			DFS(lv + 1);
			path[lv] = 0;
			checked[i] = 0;
		}
	}
}

int main()
{
	path[4] = 1;
	checked[1] = 1;

	cin >> n;

	vec.resize(n + 1);

	int a;

	for (int i = 1; i <= n; i++)
	{
		vec[i].push_back(-1); // 0번째 아무거나 집어넣기
		for (int j = 0; j < 9; j++)
		{
			cin >> a;
			vec[i].push_back(a);
		}
	}

	for (int i = 2; i <= 9; i++)
	{
		if (checked[i] == 0)
		{
			checked[i] = 1;
			path[1] = i;
			DFS(2);
			path[1] = 0;
			checked[i] = 0;
		}
	}

	cout << max1;

	return 0;
}