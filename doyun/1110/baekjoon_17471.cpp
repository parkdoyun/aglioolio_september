#include <iostream>
#include <vector>

using namespace std;

// 백준 17471 - 게리맨더링
// dfs, backtracking
// 골드 4

// 모든 a와 b 가짓수 구하기 -> backtracking
// 만약 a끼리, b끼리 인접하다면 인구 차 구하기

int visit[11]; // 0 : 방문 X, 1 : a 구역, 2 : b 구역
int path[11];
vector<vector<int>> E; // edge
int population[11]; // 인구
int min1 = 1000000000;
int n;

bool allVisited()
{
	for (int i = 1; i <= n; i++)
	{
		if (visit[i] == 0) return false;
	}
	return true;
}

void visitClr()
{
	for (int i = 1; i <= n; i++)
	{
		visit[i] = 0;
	}
}

void traversal(int now, int flag) // visit
{
	visit[now] = 1;
	for (int i = 0; i < E[now].size(); i++)
	{
		if (path[E[now][i]] == flag && visit[E[now][i]] == 0)
		{
			traversal(E[now][i], flag);
		}
	}
}

void DFS(int lv)
{
	if (lv == n + 1)
	{
		visitClr();
		// 인접한지 비교
		int now_a = -1;
		int now_b = -1;
		for (int i = 1; i <= n; i++)
		{
			if (path[i] == 1 && now_a == -1) now_a = i;
			if (path[i] == 2 && now_b == -1) now_b = i;
		}
		// 만약 a나 b의 구역이 한개도 없다면 return
		if (now_a == -1 || now_b == -1) return;

		traversal(now_a, 1); // a 구역 인접한지 비교
		traversal(now_b, 2); // b 구역 인접한지 비교

		// 인접하다면 -> 인구 차이 계산
		if (allVisited() == true)
		{
			int a_total = 0;
			int b_total = 0;
			for (int i = 1; i <= n; i++)
			{
				if (path[i] == 1)
				{
					a_total += population[i];
				}
				else b_total += population[i];
			}
			if (abs(a_total - b_total) < min1)
			{
				min1 = abs(a_total - b_total);
			}
		}
		return;
	}
	
	path[lv] = 1;
	DFS(lv + 1);
	path[lv] = 2;
	DFS(lv + 1);
}


int main()
{
	cin >> n;
	E.resize(n + 1);
	for (int i = 1; i <= n; i++) cin >> population[i];

	int cnt, tmp;
	for (int i = 1; i <= n; i++)
	{
		cin >> cnt;
		for (int j = 0; j < cnt; j++)
		{
			cin >> tmp;
			E[i].push_back(tmp);
			E[tmp].push_back(i);
		}
	}

	// backtracking
	path[1] = 1;
	DFS(2);
	path[1] = 2;
	DFS(2);

	if (min1 == 1000000000) cout << -1;
	else
	{
		cout << min1;
	}

	return 0;
}