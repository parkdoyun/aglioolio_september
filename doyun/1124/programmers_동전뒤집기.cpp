#include <string>
#include <vector>

using namespace std;

// programmers - 동전뒤집기
// greedy, DFS, backtracking

int pathW[11];
int pathH[11];

int h, w;
int answer = 100000;
vector<vector<int>> beg;
vector<vector<int>> tar;


void backtrackingW(int lv)
{
	if (lv == w)
	{
		// beginning 계산
		int cnt = 0;
		for (int i = 0; i < w; i++)
		{
			if (pathW[i] == 0) continue;
			cnt++;

			// 뒤집기
			for (int j = 0; j < h; j++)
			{
				if (beg[j][i] == 0) beg[j][i] = 1;
				else beg[j][i] = 0;
			}
		}

		for (int i = 0; i < h; i++)
		{
			if (pathH[i] == 0) continue;
			cnt++;

			// 뒤집기
			for (int j = 0; j < w; j++)
			{
				if (beg[i][j] == 0) beg[i][j] = 1;
				else beg[i][j] = 0;
			}
		}

		if (beg == tar) {
			if (cnt < answer) answer = cnt;
		}

		for (int i = 0; i < w; i++)
		{
			if (pathW[i] == 0) continue;

			// 뒤집기
			for (int j = 0; j < h; j++)
			{
				if (beg[j][i] == 0) beg[j][i] = 1;
				else beg[j][i] = 0;
			}
		}

		for (int i = 0; i < h; i++)
		{
			if (pathH[i] == 0) continue;

			// 뒤집기
			for (int j = 0; j < w; j++)
			{
				if (beg[i][j] == 0) beg[i][j] = 1;
				else beg[i][j] = 0;
			}
		}

		return;
	}

	pathW[lv] = 1;
	backtrackingW(lv + 1);
	pathW[lv] = 0;
	backtrackingW(lv + 1);
}
void backtrackingH(int lv)
{
	if (lv == h)
	{
		pathW[0] = 1;
		backtrackingW(1);
		pathW[0] = 0;
		backtrackingW(1);
		return;
	}

	pathH[lv] = 1;
	backtrackingH(lv + 1);
	pathH[lv] = 0;
	backtrackingH(lv + 1);
}


int solution(vector<vector<int>> beginning, vector<vector<int>> target) {
	int answer1 = 0;

	h = beginning.size();
	w = beginning[0].size();

	beg = beginning;
	tar = target;

	pathH[0] = 1;
	backtrackingH(1);
	pathH[0] = 0;
	backtrackingH(1);

	if (answer == 100000) answer = -1;

	answer1 = answer;
	return answer1;
}