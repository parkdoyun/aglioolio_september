#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 백준 19238 - 스타트 택시
// bfs
// 골드 3

// bfs1() : 현재 가장 가까운 출발지 찾기
// bfs2() : 목적지까지 이동
// 출발지는 겹칠 수 없어도 목적지는 겹칠 수 있음
// -> 출발지 board 기록, 목적지는 따로 벡터로
// 거리 같을 때 행이 낮은 순서, 열이 낮은 순서로 해야 함 -> pq 사용

struct node
{
	int wall; // 벽인지
	int idx = -1; // 목적지 벡터 번호
	int visit = 0; // 이 출발지 아직 안 들렸음 : 1, 들렸거나 출발지가 아니면 : 0
};

struct arr_node // 목적지 기록 위해
{
	int y;
	int x;
	int dist; // bfs queue에서만 사용
};

bool operator<(arr_node a1, arr_node a2)
{
	if (a1.dist > a2.dist) return true;
	else if (a1.dist == a2.dist && a1.y > a2.y) return true;
	else if (a1.dist == a2.dist && a1.y == a2.y && a1.x > a2.x) return true;
	return false;
}

int n, m, fuel, now_y, now_x;
int cnt = 0;
vector<arr_node> vec; // 목적지 기록 벡터
node board[21][21];
int chk[21][21];
queue<arr_node> q;
priority_queue<arr_node> pq;

int y_mov[] = { -1, 0, 1, 0 };
int x_mov[] = { 0, -1, 0, 1 };

void chkClear()
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) chk[i][j] = 0;
	}
}

// 갈 수 있는 출발지 모두 pq 삽입 -> 거리 순, 행 순, 열 순 출발지 결정
int BFS1(int start_y, int start_x) 
{
	while (!q.empty()) q.pop();
	while (!pq.empty()) pq.pop();
	chkClear();

	chk[start_y][start_x] = 1;
	q.push({ start_y, start_x, 0 });

	int idx = -1;

	while (!q.empty())
	{
		arr_node tmp = q.front();
		q.pop();

		if (board[tmp.y][tmp.x].visit == 1)
		{
			pq.push({ tmp.y, tmp.x, tmp.dist });
			/* => 이거 bfs 나가서 pq로 출발지 결정
			board[tmp.y][tmp.x].visit = 0;
			idx = board[tmp.y][tmp.x].idx; // 목적지 벡터 인덱스
			now_y = tmp.y;
			now_x = tmp.x;
			fuel -= tmp.dist;
			break;
			*/
		}

		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 1 && tmp.y + y_mov[i] <= n &&
				tmp.x + x_mov[i] >= 1 && tmp.x + x_mov[i] <= n &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0 &&
				board[tmp.y + y_mov[i]][tmp.x + x_mov[i]].wall == 0)
			{
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] = 1;
				q.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.dist + 1 });
			}
		}
	}
	return idx;
}

// 목적지까지 이동
int BFS2(int start_y, int start_x, int end_y, int end_x)
{
	while (!q.empty()) q.pop();
	chkClear();

	chk[start_y][start_x] = 1;
	q.push({ start_y, start_x, 0 });

	while (!q.empty())
	{
		arr_node tmp = q.front();
		q.pop();

		if (tmp.y == end_y && tmp.x == end_x)
		{
			now_y = tmp.y;
			now_x = tmp.x;
			fuel -= tmp.dist;
			return tmp.dist;
		}

		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 1 && tmp.y + y_mov[i] <= n &&
				tmp.x + x_mov[i] >= 1 && tmp.x + x_mov[i] <= n &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0 &&
				board[tmp.y + y_mov[i]][tmp.x + x_mov[i]].wall == 0)
			{
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] = 1;
				q.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.dist + 1 });
			}
		}
	}
	return -1; // 목적지로 이동 못 할 경우
}
int main()
{
	cin >> n >> m >> fuel;
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> board[i][j].wall;
		}
	}

	int start_y, start_x;
	cin >> start_y >> start_x;

	cnt = 0; // 이동시킨 손님 수

	int y, x;
	for (int i = 0; i < m; i++)
	{
		// 출발지
		cin >> y >> x;
		board[y][x].idx = i;
		board[y][x].visit = 1;

		// 목적지
		cin >> y >> x;
		vec.push_back({ y, x });
	}

	now_y = start_y;
	now_x = start_x;

	// bfs
	while (true)
	{
		int vec_idx = BFS1(now_y, now_x);
		if (pq.size() == 0) break;

		arr_node tmp = pq.top();

		board[tmp.y][tmp.x].visit = 0;
		vec_idx = board[tmp.y][tmp.x].idx; // 목적지 벡터 인덱스
		now_y = tmp.y;
		now_x = tmp.x;
		fuel -= tmp.dist;
		
		if (fuel < 0)
		{
			break;
		}

		// 목적지까지 이동
		int f = BFS2(now_y, now_x, vec[vec_idx].y, vec[vec_idx].x);
		if (fuel < 0 || f == -1) break;
		fuel += f * 2;
		cnt++;
	}

	if (fuel < 0 || cnt != m)
	{
		cout << -1;
	}
	else cout << fuel;

	return 0;
}