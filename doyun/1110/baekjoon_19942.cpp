#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 백준 19942 - 다이어트
// 골드 5
// dfs, backtracking

// 식재료 모든 조건 다 찾아보기
// 모든 조건 다 찾고 그 중 최소 찾기

int n, mp, mf, ms, mv;
int min1 = 1000000000;

int path[16]; // backtracking 0 : use, 1 : no-use
vector<string> vec; // 결과 담는 배열, 오름차순 정렬해야 하므로
vector<vector<int>> ingredient;

void DFS(int lv)
{
	if (lv == n)
	{
		// 계산
		int tmp[4] = { 0 };
		int price = 0;
		string str_tmp = "";
		for (int i = 0; i < n; i++)
		{
			if (path[i] == 0) continue;
			for (int j = 0; j < 4; j++)
			{
				tmp[j] += ingredient[i][j];
			}
			str_tmp = str_tmp + to_string(i + 1) + " ";
			price += ingredient[i][4];
		}

		if (!(tmp[0] >= mp && tmp[1] >= mf && tmp[2] >= ms && tmp[3] >= mv))
		{
			return;
		}
		if (price == min1) // 그냥 추가
		{
			vec.push_back(str_tmp);
		}
		else if (price < min1) // 새로 추가
		{
			min1 = price;
			vec.clear();
			vec.push_back(str_tmp);
		}

		return;
	}
	path[lv] = 0;
	DFS(lv + 1);
	path[lv] = 1;
	DFS(lv + 1);
}

int main()
{
	cin >> n >> mp >> mf >> ms >> mv;

	int p, f, s, v, c;
	for (int i = 0; i < n; i++)
	{
		cin >> p >> f >> s >> v >> c;
		vector<int> tmp_vec = {p, f, s, v, c};
		ingredient.push_back(tmp_vec);
	}
	
	// dfs
	path[0] = 0;
	DFS(1);
	path[0] = 1;
	DFS(1);

	sort(vec.begin(), vec.end()); // 오름차순 정렬

	if (vec.empty()) cout << -1;
	else
	{
		// 결과 출력
		cout << min1 << '\n' << vec[0];
	}

	return 0;
}