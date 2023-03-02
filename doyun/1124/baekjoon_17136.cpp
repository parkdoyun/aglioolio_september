#include <iostream>

using namespace std;

// 백준 17136 - 색종이 붙이기
// brute-force, DFS
// 골드 2

// 색종이로 덮을 수 있는 모든 가짓수 다 해본다 (DFS)
// 색종이로 다 덮을 수 있으면 덮은 색종이 수 카운트

// 만약 덮을 부분 발견하고 해당 칸 색종이로 덮을 수 있으면
// 다음 덮을 색종이 부분으로 DFS

// 색종이로 안 덮어지면 DFS return

int min1 = 10000000;
int path[25];
int cp[11][11];
int paper_n[6] = { 0, 5, 5, 5, 5, 5 }; // 색종이 갯수

void findNext(int y, int x, int &y1, int &x1) // 다음 색종이로 덮어야 하는 부분 찾기
{
	for (int i = y; i < 10; i++)
	{
		if (i == y)
		{
			for (int j = x; j < 10; j++)
			{
				if (cp[i][j] == 1)
				{
					y1 = i;
					x1 = j;
					return;
				}
			}
		}
		else
		{
			for (int j = 0; j < 10; j++)
			{
				if (cp[i][j] == 1)
				{
					y1 = i;
					x1 = j;
					return;
				}
			}
		}
	}
	y1 = -1; // 색종이로 덮을 부분 X -> 다 덮음
	x1 = -1;
}

int printChk(int y, int x, int n) // 색종이로 덮을 수 있는지 확인
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (cp[y + i][x + j] == 0) return -1;
		}
	}
	return 1;
}

void print(int y, int x, int n, int val) // 색종이로 덮기 또는 원상복구
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cp[y + i][x + j] = val;
		}
	}
}

void DFS(int y, int x, int cnt) {
	int next_y, next_x;
	for (int i = 1; i <= 5; i++)
	{
		if (paper_n[i] == 0) continue;
		if (printChk(y, x, i) == 1) // i 크기의 색종이로 덮을 수 있다면
		{
			print(y, x, i, 0); // 색종이로 덮기
			paper_n[i]--; // 색종이 카운트 줄이기
			findNext(y, x, next_y, next_x);
			if (next_y != -1 && next_x != -1)
			{ // 다음으로 넘어감
				DFS(next_y, next_x, cnt + 1);
			}
			else // 색종이로 다 덮음 -> 색종이 갯수 카운트
			{
				if (min1 > cnt) min1 = cnt;
			}
			paper_n[i]++; // 카운트 원상복구
			print(y, x, i, 1); // 덮은 거 원상복구
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);


	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) cin >> cp[i][j];
	}

	int start_y, start_x;
	findNext(0, 0, start_y, start_x);
	if (start_y == -1 && start_x == -1) // 색종이 필요 없다면 바로 0 출력
	{
		cout << 0;
		return 0;
	}
	DFS(start_y, start_x, 1);

	if (min1 == 10000000) min1 = -1;
	cout << min1;

	return 0;
}