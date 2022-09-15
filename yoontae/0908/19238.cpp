#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Coord
{
	int y; 
	int x;
};

bool cmp(Coord A, Coord B)
{
	if (A.y < B.y)
		return true;
	if (A.y > B.y)
		return false;
	if (A.x < B.x)
		return true;
	if (A.x > B.x)
		return false;
	return false;
}

int N, M, F;
int MAP[21][21];
Coord Taxi;
vector<Coord> Guests;
vector<Coord> Dests;
Coord Guest;
Coord Dest;
int Done[500];

void input()
{
	cin >> N >> M >> F;

	for (int y = 1; y <= N; y++)
		for (int x = 1; x <= N; x++)
			cin >> MAP[y][x];

	cin >> Taxi.y >> Taxi.x;

	for (int i = 0; i < M; i++)
	{
		int y1, x1, y2, x2;
		cin >> y1 >> x1 >> y2 >> x2;
		Guests.push_back({ y1,x1 });
		Dests.push_back({ y2,x2 });
	}
}

int find_closest(int sy, int sx)
{
	queue<Coord> q;
	int visited[21][21] = {0};

	visited[sy][sx] = 1;

	q.push({ sy,sx });

	while (!q.empty())
	{
		Coord now = q.front();
		q.pop();

		int dy[] = { -1,0,0,1 };
		int dx[] = { 0,-1,1,0 };

		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 1 || ny > N || nx < 1 || nx > N)
				continue;

			if (MAP[ny][nx] == 1)
				continue;

			if (visited[ny][nx] > 0)
				continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx });
		}
	}

	int closest = 2134567890;
	int closestIdx = -1;

	for (int i = 0; i < (int)(Guests.size()); i++)
	{
		if (Done[i] == 1)
			continue;

		if (visited[Guests[i].y][Guests[i].x] < closest)
		{
			closest = visited[Guests[i].y][Guests[i].x];
			closestIdx = i;
		}
		else if (visited[Guests[i].y][Guests[i].x] == closest)
		{
			if (Guests[i].y < Guests[closestIdx].y)
			{
				closest = visited[Guests[i].y][Guests[i].x];
				closestIdx = i;
			}
			else if (Guests[i].y == Guests[closestIdx].y)
			{
				if (Guests[i].x < Guests[closestIdx].x)
				{
					closest = visited[Guests[i].y][Guests[i].x];
					closestIdx = i;
				}
			}
		}
	}

	Guest = Guests[closestIdx];
	Dest = Dests[closestIdx];
	Done[closestIdx] = 1;
	return visited[Guests[closestIdx].y][Guests[closestIdx].x] - 1;
}

int goToDest(int sy, int sx, int ey, int ex)
{
	queue<Coord> q;
	int visited[21][21] = { 0 };

	visited[sy][sx] = 1;

	q.push({ sy,sx });

	while (!q.empty())
	{
		Coord now = q.front();
		q.pop();

		if (now.y == ey && now.x == ex)
		{
			return visited[ey][ex] - 1;
		}

		int dy[] = { -1,0,0,1 };
		int dx[] = { 0,-1,1,0 };

		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 1 || ny > N || nx < 1 || nx > N)
				continue;

			if (MAP[ny][nx] == 1)
				continue;

			if (visited[ny][nx] > 0)
				continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx });
		}
	}

	return visited[ey][ex] - 1;
}

void solution()
{
	int cnt = 0;

	while (cnt != M)
	{
		int fuelUsed = find_closest(Taxi.y, Taxi.x);

		if (F - fuelUsed <= 0)
		{
			cout << -1;
			return;
		}
		if (fuelUsed == -1)
		{
			cout << -1;
			return;
		}

		F -= fuelUsed;

		fuelUsed = goToDest(Guest.y, Guest.x, Dest.y, Dest.x);

		if (fuelUsed == -1)
		{
			cout << -1;
			return;
		}

		if (F - fuelUsed < 0)
		{
			cout << -1;
			return;
		}
		else
		{
			F += fuelUsed;
			Taxi = Dest;
			cnt++;
		}
	}
	
	cout << F;
}

int main()
{
	input();
	solution();

	return 0;
}