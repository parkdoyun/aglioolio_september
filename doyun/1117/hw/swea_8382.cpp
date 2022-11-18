#include <iostream>

using namespace std;

// swea 8382 - 방향 전환
// BFS, dijkstra -> 시간 초과
// 방향 그때마다 계산해서 원하는 쪽으로 위치 이동

int x_mov[] = { -1, 1, -1, 1 };
int y_mov[] = { -1, -1, 1, 1 }; // 가로부터나 세로부터나 상관 없음, 동일

int calDir(int tmp_x, int tmp_y, int x2, int y2)
{
	if (tmp_x > x2)
	{
		if (tmp_y > y2)
		{
			return 0;
		}
		else return 2;
	}
	else
	{
		if (tmp_y > y2)
		{
			return 1;
		}
		else return 3;
	}

	return -1;
}

int main()
{
	int T, x1, y1, x2, y2;
	int x_dist, y_dist;
	cin >> T;
	
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> x1 >> y1 >> x2 >> y2;

		int cnt = 0;
		int tmp_x = x1;
		int	tmp_y = y1;


		// 거리 1 남거나 위치 맞을때까지
		// 방향에 맞춰 이동
		while (abs(tmp_x - x2) + abs(tmp_y - y2) > 1)
		{
			int idx = calDir(tmp_x, tmp_y, x2, y2);
			cnt += 2;
			tmp_x = tmp_x + x_mov[idx];
			tmp_y = tmp_y + y_mov[idx];
		}

		if (abs(tmp_x - x2) + abs(tmp_y - y2) == 1) cnt++;

		cout << '#' << tc << ' ' << cnt << '\n';

	}


	return 0;
}