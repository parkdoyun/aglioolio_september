#include <iostream>
#include <queue>

using namespace std;

// 백준 3190 - 뱀
// BFS, queue
// 골드 4

// 뱀을 queue로 => head는 q.back(), tail은 q.front()

int n, k, l;
int board[101][101];
// 상, 우, 하, 좌 (숫자 커질수록 오른쪽 이동, 숫자 작아질수록 왼쪽 이동)
int y_mov[] = { -1, 0, 1, 0 };
int x_mov[] = { 0, 1, 0, -1 };
int now_dir = 1; // 처음에 오른쪽

struct direction
{
	int time;
	int dir; // -1 : 왼쪽, 1 : 오른쪽
};
struct node
{
	int y;
	int x;
};
queue<direction> q_dir;
queue<node> snake; // 뱀

int BFS()
{
	snake.push({ 0, 0 });
	node head = snake.back();
	node tail = snake.front();
	board[head.y][head.x] = 1;

	int now_time = 1;

	while (!q_dir.empty()) // 방향 전환
	{
		direction tmp = q_dir.front();
		q_dir.pop();

		// tmp의 시간만큼 이동
		// 그 전에 벽이나 나에게 부딪치면 나가기
		int out_flag = -1;
		for (int j = now_time; j <= tmp.time; j++)
		{
			if (head.y + y_mov[now_dir] >= 0 && head.y + y_mov[now_dir] < n && 
				head.x + x_mov[now_dir] >= 0 && head.x + x_mov[now_dir] < n &&
				board[head.y + y_mov[now_dir]][head.x + x_mov[now_dir]] != 1)
			{
				snake.push({ head.y + y_mov[now_dir], head.x + x_mov[now_dir] });
				if (board[head.y + y_mov[now_dir]][head.x + x_mov[now_dir]] != 2)
				{
					// 사과 없다면, 꼬리 움직이기
					board[tail.y][tail.x] = 0;
					snake.pop();
				}
				board[head.y + y_mov[now_dir]][head.x + x_mov[now_dir]] = 1;
				head = snake.back();
				tail = snake.front();
			}
			else // 나나 벽에 부딪치면 나가기
			{
				now_time = j;
				out_flag = 0;
				break;
			}
		}
		if (out_flag == 0) break;

		// 방향 전환하기
		now_time = tmp.time + 1;
		now_dir += tmp.dir;
		if (now_dir < 0) now_dir = 3;
		else if (now_dir > 3) now_dir = 0;
	}

	// 방향 전환 이후에 더 움직일 수 있는지 확인
	if (q_dir.empty()) // 더 움직일 수 있는지 확인
	{
		while (true)
		{
			if (head.y + y_mov[now_dir] >= 0 && head.y + y_mov[now_dir] < n &&
				head.x + x_mov[now_dir] >= 0 && head.x + x_mov[now_dir] < n &&
				board[head.y + y_mov[now_dir]][head.x + x_mov[now_dir]] != 1)
			{
				snake.push({ head.y + y_mov[now_dir], head.x + x_mov[now_dir] });
				if (board[head.y + y_mov[now_dir]][head.x + x_mov[now_dir]] != 2)
				{
					// 사과 없다면, 꼬리 움직이기
					board[tail.y][tail.x] = 0;
					snake.pop();
				}
				board[head.y + y_mov[now_dir]][head.x + x_mov[now_dir]] = 1;
				head = snake.back();
				tail = snake.front();
			}
			else // 나나 벽에 부딪치면 나가기
			{
				break;
			}
			now_time++;
		}
	}

	return now_time;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);


	cin >> n >> k;
	int y, x;
	for (int i = 0; i < k; i++)
	{
		cin >> y >> x;
		board[--y][--x] = 2; // 사과
	}

	cin >> l;
	char c;
	for (int i = 0; i < l; i++)
	{
		cin >> x >> c;
		if (c == 'L') q_dir.push({ x, -1 });
		else q_dir.push({ x, 1 });
	}

	cout << BFS();

	return 0;
}