#include <iostream>

using namespace std;

// swea 4008 - 숫자 만들기
// DFS, backtracking
// 모든 경우의 수 다 하고 최대 최소 구하기

int n;
int path[13]; // 0 : +, 1 : -, 2 : *, 3 : /
int arr[13];
int operation[4]; // 연산자 갯수
int max1 = -100000001;
int min1 = 100000001;

int cal()
{
	int res = arr[0];
	for (int i = 0; i < n - 1; i++)
	{
		if (path[i] == 0)
		{
			res += arr[i + 1];
		}
		else if (path[i] == 1)
		{
			res -= arr[i + 1];
		}
		else if (path[i] == 2)
		{
			res *= arr[i + 1];
		}
		else // 3
		{
			res /= arr[i + 1];
		}
	}

	return res;
}

void DFS(int lv)
{
	if (lv == n - 1) {
		// 계산
		int tmp_res = cal();
		if (tmp_res > max1) max1 = tmp_res;
		if (tmp_res < min1) min1 = tmp_res;
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		if (operation[i] > 0)
		{
			operation[i]--;
			path[lv] = i;
			DFS(lv + 1);
			path[lv] = -1;
			operation[i]++;
		}
	}
}

int main()
{
	int T;
	cin >> T;
	
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> n;
		max1 = -100000001;
		min1 = 100000001;

		for (int i = 0; i < 4; i++)
		{
			cin >> operation[i];
		}

		for (int i = 0; i < n; i++)
		{
			cin >> arr[i];
		}

		for (int i = 0; i < 4; i++)
		{
			if (operation[i] > 0)
			{
				operation[i]--;
				path[0] = i;
				DFS(1);
				path[0] = -1;
				operation[i]++;
			}
		}
		
		cout << '#' << tc << ' ' << max1 - min1 << '\n';

	}

	return 0;
}