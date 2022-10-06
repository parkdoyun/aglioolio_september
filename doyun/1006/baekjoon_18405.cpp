#include <iostream>
#include <queue>

using namespace std;

// ¹éÁØ 18405 - °æÀïÀû Àü¿°
// bfs, brute-force
// °ñµå 5

int n, k, s, x, y;

int arr[201][201];
int chk[201][201];

struct virus
{
	int y;
	int x;
	int n;
	int time;
};

bool operator<(virus v1, virus v2)
{
	if (v1.time > v2.time) return true;
	else if (v1.time == v2.time && v1.n > v2.n) return true;
	return false;
}

int x_mov[] = { 0, 0, -1, 1 };
int y_mov[] = { -1, 1, 0, 0 };

priority_queue<virus> pq;
void BFS()
{
	while (!pq.empty())
	{
		virus tmp = pq.top();
		pq.pop();

		if (tmp.time >= s) break;

		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 1 && tmp.y + y_mov[i] <= n &&
				tmp.x + x_mov[i] >= 1 && tmp.x + x_mov[i] <= n &&
				arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0 &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0)
			{
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] = 1;
				arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]] = tmp.n;
				pq.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.n, tmp.time + 1 });
			}
		}

	}
}

int main()
{
	cin >> n >> k;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> arr[i][j];
			if (arr[i][j] != 0)
			{
				pq.push({ i, j, arr[i][j], 0 });
				chk[i][j] = 1;
			}
		}
	}

	cin >> s >> x >> y;

	BFS();

	cout << arr[x][y];



	return 0;
}