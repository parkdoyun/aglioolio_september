#include <iostream>

using namespace std;

// swea 1486 - 장훈이의 높은 선반
// DFS, backtracking
// 탑의 높이 모두 구함
// 가장 차이 안 나는 것 출력

int min1 = 10000000000;
int n, b;
int arr[21];
int path[21];

void DFS(int lv)
{
	if (lv == n)
	{
		// 계산
		int tmp = 0;
		for (int i = 0; i < n; i++)
		{
			if (path[i] == 1) tmp += arr[i];
		}
		if (tmp >= b && abs(tmp - b) < min1)
		{
			min1 = abs(tmp - b);
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
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> n >> b;
		min1 = 10000000000;

		for (int i = 0; i < n; i++)
		{
			cin >> arr[i];
		}

		// backtracking
		path[0] = 0;
		DFS(1);
		path[0] = 1;
		DFS(1);

		cout << '#' << tc << ' ' << min1 << '\n';

	}


	return 0;
}