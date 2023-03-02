#include <iostream>
#include <vector>

using namespace std;

// softeer 인증평가 2차 - 사물인식 최소 면적 산출 프로그램
// backtracking
// 별 3

struct node
{
	int y;
	int x;
	int color;
};
int n, k;
int path[21]; // backtracking
vector<node> V;
vector<vector<int>> color_vec;
int minSize = 999999999;

// 이미 크다면 자른다
void backtracking(int lv, int max_y, int max_x, int min_y, int min_x)
{
	if (lv == k + 1)
	{
		int tmp_s = (max_y - min_y) * (max_x - min_x);
		if (tmp_s < minSize) minSize = tmp_s;
		return;
	}

	if (color_vec[lv].empty()) // 만약 해당 색깔 점 없다면 다음으로 넘어감
	{
		backtracking(lv + 1, max_y, max_x, min_y, min_x);
	}
	else
	{
		for (int i = 0; i < color_vec[lv].size(); i++)
		{
			int y1 = max_y; int x1 = max_x;
			int y2 = min_y; int x2 = min_x;
			path[lv] = color_vec[lv][i];
			node tmp = V[path[lv]];
			if (tmp.y > max_y) y1 = tmp.y;
			if (tmp.x > max_x) x1 = tmp.x;
			if (tmp.y < min_y) y2 = tmp.y;
			if (tmp.x < min_x) x2 = tmp.x;
			if ((y1 - y2) * (x1 - x2) >= minSize) continue;
			backtracking(lv + 1, y1, x1, y2, x2);
			path[lv] = 0;
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> k;
	V.resize(n + 1);
	color_vec.resize(k + 1);

	int x, y, c;
	for (int i = 1; i <= n; i++)
	{
		cin >> x >> y >> c;
		V[i].y = y;
		V[i].x = x;
		V[i].color = c;
		color_vec[c].push_back(i);
	}

	for (int i = 1; i <= k; i++)
	{
		if (!color_vec[i].empty()) // 색깔 있다면
		{
			for (int j = 0; j < color_vec[i].size(); j++)
			{
				node tmp = V[color_vec[i][j]];
				path[i] = color_vec[i][j];
				backtracking(i + 1, tmp.y, tmp.x, tmp.y, tmp.x);
			}
			break;
		}
	}

	cout << minSize;

	return 0;
}