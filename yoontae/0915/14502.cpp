#include <iostream>
#include <queue>

using namespace std;

struct Coord
{
	int y;
	int x;
};

int N, M;
int MAP[8][8];
int MAP_copy[8][8];
int maxCnt;

void input()
{
	cin >> N >> M;

	for (int y = 0; y < N; y++)
		for (int x = 0; x < M; x++)
			cin >> MAP[y][x];
}

void virusSpread(int sy, int sx)
{
	queue<Coord> q;

	q.push({ sy,sx });

	while (!q.empty())
	{
		Coord now = q.front();
		q.pop();

		int dy[] = { -1,1,0,0 };
		int dx[] = { 0,0,-1,1 };

		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= M)
				continue;

			if (MAP_copy[ny][nx] != 0)
				continue;

			MAP_copy[ny][nx] = 2;
			q.push({ ny,nx });
		}
	}
}

void setUpWall(int level, int py, int px)
{
	if (level == 3)
	{
		int cnt = 0;

		for (int y = 0; y < N; y++)
			for (int x = 0; x < M; x++)
				MAP_copy[y][x] = MAP[y][x];
		
		for (int y = 0; y < N; y++)
			for (int x = 0; x < M; x++)
			{
				if (MAP_copy[y][x] == 2)
					virusSpread(y, x);
			}

		for (int y = 0; y < N; y++)
			for (int x = 0; x < M; x++)
			{
				if (MAP_copy[y][x] == 0)
					cnt++;
			}

		if (cnt > maxCnt)
			maxCnt = cnt;

		return;
	}


	for (int y = py; y < N; y++)
	{
		for (int x = px; x < M; x++)
		{
			if (MAP[y][x] != 0)
				continue;

			MAP[y][x] = 1;
			setUpWall(level + 1, y, x);
			MAP[y][x] = 0;
		}
		px = 0;
	}
		
}

void solution()
{
	setUpWall(0, 0, 0);
	cout << maxCnt;
}

int main()
{
	input();
	solution();

	return 0;
}
