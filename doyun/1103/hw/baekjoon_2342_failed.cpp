#include <iostream>
#include <cmath>

using namespace std;

// 백준 Dance Dance Revolution
// 반례 : 1 3 2 4 1 3 2 4 0 (20 나와야 하는데 21 나옴)

// 왼발을 사용해야 힘이 더 적게 드는지 오른발을 사용해야 더 적게 드는지?
// 해당 발판으로부터 현재 발1, 발2의 위치 비교 후 적은 쪽이 옮기도록 => 이렇게 하니 틀림
// DP[i-1] 까지는 최소

// DP[0] 발1->발1, DP[1] 1->2, DP[2] 2->1, DP[3] 2->2 가짓수 모두 구하기
// 시작 1, 2는 최소로 고른다

struct node
{
	int y = 1;
	int x = 1;
};

node panel[5];
node foot[100002][4][2]; // 발 1, 2
int tmp_dist[4][2]; // 임시 거리 미리 계산, tmp_dist[i][0] : 1번이 움직이는 경우, tmp_dist[i][1] : 2번이 움직이는 경우
int DP[4][100002];

int calDist(node p, node n) // p : 이동하려는 곳, n : 현재 위치
{
	// 인접한지
	int y_d = abs(p.y - n.y);
	int x_d = abs(p.x - n.x);
	if (y_d == 0 && x_d == 0) return 1;
	else if ((y_d == 0 && x_d == 1) || (y_d == 1 && x_d == 0)) return 2;
	else if ((y_d == 0 && x_d == 2) || (y_d == 2 && x_d == 0)) return 4;
	return 3;
}
int main()
{
	int n;
	panel[0] = { 1, 1 };
	panel[1] = { 0, 1 };
	panel[2] = { 1, 0 };
	panel[3] = { 2, 1 };
	panel[4] = { 1, 2 };
	int cnt = 0;
	while (true)
	{
		cin >> n;
		if (n == 0) break;
		cnt++;
		if (cnt == 1) // 기저 조건
		{
			int tmp_d = calDist(panel[n], { 1, 1 });
			for (int i = 0; i < 4; i++)
			{
				DP[i][cnt] = tmp_d;
			}
			// DP[0] : 1 이동
			foot[1][0][0] = panel[n];
			// DP[1] : 2 이동
			foot[1][1][1] = panel[n];
			// DP[2] : 1 이동
			foot[1][2][0] = panel[n];
			// DP[3] : 2 이동
			foot[1][3][1] = panel[n];
		}
		else
		{
			// DP[i][cnt-1] + calDist(panel[n], foot[i])가 최소인 것 넣기
			// DP[0], DP[2]가 발1
			// DP[1], DP[3]가 발2
			// 거리 미리 전부 계산
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					tmp_dist[i][j] = calDist(panel[n], foot[cnt-1][i][j]);
				}
			}

			// 1 -> 1
			if (DP[0][cnt - 1] + tmp_dist[0][0] < DP[2][cnt - 1] + tmp_dist[2][0])
			{
				DP[0][cnt] = DP[0][cnt - 1] + tmp_dist[0][0];
				foot[cnt][0][0] = panel[n];
				foot[cnt][0][1] = foot[cnt - 1][0][1];
			}
			else
			{
				DP[0][cnt] = DP[2][cnt - 1] + tmp_dist[2][0];
				foot[cnt][0][0] = panel[n];
				foot[cnt][0][1] = foot[cnt - 1][2][1];
			}
			
			// 1 -> 2
			if (DP[0][cnt - 1] + tmp_dist[0][1] < DP[2][cnt - 1] + tmp_dist[2][1])
			{
				DP[1][cnt] = DP[0][cnt - 1] + tmp_dist[0][1];
				foot[cnt][1][0] = foot[cnt - 1][0][0];
				foot[cnt][1][1] = panel[n];
			}
			else
			{
				DP[1][cnt] = DP[2][cnt - 1] + tmp_dist[2][1];
				foot[cnt][1][0] = foot[cnt - 1][2][0];
				foot[cnt][1][1] = panel[n];
			}

			// 2 -> 1
			if (DP[1][cnt - 1] + tmp_dist[1][0] < DP[3][cnt - 1] + tmp_dist[3][0])
			{
				DP[2][cnt] = DP[1][cnt - 1] + tmp_dist[1][0];
				foot[cnt][2][0] = panel[n];
				foot[cnt][2][1] = foot[cnt - 1][1][1];
			}
			else
			{
				DP[2][cnt] = DP[3][cnt - 1] + tmp_dist[3][0];
				foot[cnt][2][0] = panel[n];
				foot[cnt][2][1] = foot[cnt - 1][3][1];
			}

			// 2 -> 2
			if (DP[1][cnt - 1] + tmp_dist[1][1] < DP[3][cnt - 1] + tmp_dist[3][1])
			{
				DP[3][cnt] = DP[1][cnt - 1] + tmp_dist[1][1];
				foot[cnt][3][0] = foot[cnt - 1][1][0];
				foot[cnt][3][1] = panel[n];
			}
			else
			{
				DP[3][cnt] = DP[3][cnt - 1] + tmp_dist[3][1];
				foot[cnt][3][0] = foot[cnt - 1][3][0];
				foot[cnt][3][1] = panel[n];
			}
			
		}
	}

	// DP[i][cnt] 중 최소 출력
	int min = DP[0][cnt];
	for (int i = 1; i < 4; i++)
	{
		if (min > DP[i][cnt]) min = DP[i][cnt];
	}
	cout << min;

	return 0;
}