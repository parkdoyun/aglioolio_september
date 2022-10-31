#include <iostream>
#include <queue>

using namespace std;

// πÈ¡ÿ 4485 - ≥Ïªˆ ø  ¿‘¿∫ æ÷∞° ¡©¥Ÿ¡ˆ?
// dijkstra
// ∞ÒµÂ 4

int arr[126][126];
int money[126][126];
int chk[126][126];
int n;

int y_mov[] = { 0, 0, -1, 1 };
int x_mov[] = { -1, 1, 0, 0 };

struct node
{
	int y;
	int x;
	int cost = 0; // ¿“¥¬ µ∑
};

bool operator<(node n1, node n2)
{
	if (n1.cost > n2.cost) return true;
	return false;
}

priority_queue<node> pq;

void dijkstra()
{
	while (!pq.empty()) pq.pop();

	pq.push({ 0, 0, arr[0][0] });

	while (!pq.empty())
	{
		node tmp = pq.top();
		pq.pop();
		if (chk[tmp.y][tmp.x] == 1) continue;
		chk[tmp.y][tmp.x] = 1;

		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 0 && tmp.y + y_mov[i] < n &&
				tmp.x + x_mov[i] >= 0 && tmp.x + x_mov[i] < n &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == -1 &&
				money[tmp.y + y_mov[i]][tmp.x + x_mov[i]] > tmp.cost + arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]])
			{
				money[tmp.y + y_mov[i]][tmp.x + x_mov[i]] = tmp.cost + arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]];
				pq.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], money[tmp.y + y_mov[i]][tmp.x + x_mov[i]] });
			}
		}

	}
}


int main()
{
	int cnt = 1;
	while (true)
	{
		cin >> n;
		if (n == 0) break;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> arr[i][j];
				money[i][j] = 10000000;
				chk[i][j] = -1;
			}
		}

		// dijkstra
		dijkstra();
		cout << "Problem " << cnt << ": " << money[n - 1][n - 1] << '\n';
		cnt++;
	}

	return 0;
}