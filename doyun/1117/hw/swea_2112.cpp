#include <iostream>

using namespace std;

// swea 2112 - 보호 필름
// DFS, backtracking
// 약품 투입하는 모든 가짓수 세기 (투입 안 하는 것 포함)
// 성능검사 통과 -> 최소 약품 수 세기
// 시간 초과 -> DFS 중간에 끊기 & chk 함수 중간에 끊기

int d, w, k;
int film[14][21];
int film_cp[14][21]; // arr copy

int path[14];// -1 : 약품 X, 0 : 0으로 , 1 : 1로 처리
int min1 = 10000000000;

void arrCp()
{
	for (int i = 0; i < d; i++) 
	{
		for (int j = 0; j < w; j++)
		{
			if (path[i] == -1) film_cp[i][j] = film[i][j];
			else if (path[i] == 0) film_cp[i][j] = 0;
			else film_cp[i][j] = 1;
		}
	}
}

int chk()
{
	int res = 0;
	for (int i = 0; i < w; i++)
	{
		int idx = 0;
		int max_cnt = 0;
		int cnt;
		while (idx < d - 1)
		{
			cnt = 1;
			while (idx < d - 1 && film_cp[idx][i] == film_cp[idx + 1][i])
			{
				cnt++;
				idx++;
			}
			idx++;
			if (max_cnt < cnt) max_cnt = cnt;
		}
		if (max_cnt >= k) res++;
		else return -1;
	}
	return res;
}

// 약품 카운트가 min1보다 클 경우 무조건 return
void DFS(int lv, int med_cnt)
{
	if (med_cnt >= min1 || min1 == 0) return;
	if (lv == d)
	{
		// 보호필름 계산
		arrCp();
		int tmp_res = chk();

		// 합격인지 계산
		if (tmp_res == w)
		{
			int tmp_cnt = 0;
			for (int i = 0; i < d; i++)
			{
				if (path[i] != -1) tmp_cnt++;
			}
			if (tmp_cnt < min1)
			{
				min1 = tmp_cnt;
			}
		}

		return;
	}
	
	path[lv] = -1;
	DFS(lv + 1, med_cnt);

	path[lv] = 0;
	DFS(lv + 1, med_cnt + 1);

	path[lv] = 1;
	DFS(lv + 1, med_cnt + 1);

}


int main()
{
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> d >> w >> k;
		min1 = 10000000000;

		for (int i = 0; i < d; i++)
		{
			for (int j = 0; j < w; j++) cin >> film[i][j];
		}

		// 약품 안 넣고 되는지 먼저 확인
		for (int i = 0; i < w; i++) path[i] = -1;
		arrCp();
		if (chk() == w)
		{
			cout << '#' << tc << ' ' << 0 << '\n';
			continue;
		}

		path[0] = -1;
		DFS(1, 0);

		path[0] = 0;
		DFS(1, 1);

		path[0] = 1;
		DFS(1, 1);

		cout << '#' << tc << ' ' << min1 << '\n';
	}

	return 0;
}